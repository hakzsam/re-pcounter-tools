#include <windows.h>
#include <wingdi.h>

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>

#include <gl/gl.h>
#include <GL/glut.h>

/* Set up NVPMAPI. */
#define INSTRUMENTATION_ENABLED
#define NVPM_INITGUID
#include "NvPmApi.Manager.h"
#ifdef _WIN64
#define PATH_TO_NVPMAPI_CORE L"lib\\perfkit\\bin\\win7_x64\\NvPmApi.Core.dll"
#else
#define PATH_TO_NVPMAPI_CORE L"lib\\perfkit\\bin\\win7_x86\\NvPmApi.Core.dll"
#endif

/* apitrace or a simple OpenGL scene. */
#define USE_APITRACE
#ifdef USE_APITRACE
#define PATH_TO_APITRACE "\"c:\\Users\\root\\Downloads\\apitrace-msvc-latest\\apitrace-msvc\\x86\\bin\\glretrace.exe\""
#endif

/* Simple singleton implementation for grabbing the NvPmApi. */
static NvPmApiManager S_NVPMManager;
extern NvPmApiManager *GetNvPmApiManager() {return &S_NVPMManager;}
NVPMContext g_hNVPMContext;
const NvPmApi *GetNvPmApi() {return S_NVPMManager.Api();}

/* File used to output the list of available graphics counters. */
static FILE *output = NULL;

const char *pc_name = "shader_busy";
static int process_is_running = 1;

static int launch_glretrace()
{
    HANDLE child_out_rd = NULL, child_out_wr = NULL;
    SECURITY_ATTRIBUTES sa;
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    BOOL success;

    /* Set the bInheritHandle flag so pipe handles are inherited. */
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    /* Create a pipe for the child process's STDOUT. */
    if (!CreatePipe(&child_out_rd, &child_out_wr, &sa, 0))
        return -1;

    /* Set up members of the PROCESS_INFORMATION structure. */
    ZeroMemory(&pi, sizeof(pi));

    /* Set up members of the STARTUPINFO structure.
     * This structure specifies the STDIN and STDOUT handles for redirection. */
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdError  = child_out_wr;
    si.hStdOutput = child_out_wr;
    si.dwFlags |= STARTF_USESTDHANDLES;

    /* Create the child process. */
    success = CreateProcess(
        NULL,
        "\"c:\\Users\\root\\Downloads\\apitrace-msvc-latest\\apitrace-msvc\\x86\\bin\\glretrace.exe\" \"c:\\Users\\root\\Downloads\\apitrace-msvc-latest\\apitrace-msvc\\x86\\bin\\trimed.806.trim.trace\"",
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi);           // Pointer to PROCESS_INFORMATION structure

    if (!success) {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return -1;
    }

    /* Wait until child process exits. */
    WaitForSingleObject(pi.hProcess, INFINITE);
    process_is_running = 0;

    /* Close process and thread handles. */
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

static int run_thread(HANDLE *th, LPTHREAD_START_ROUTINE callback)
{
    DWORD thid;
    *th = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)callback,
                       NULL, 0, &thid);
    if (*th == NULL) {
        printf("CreateThread failed: (%d).\n", GetLastError());
        return -1;
    }
    return 0;
}

static int perfkit_init()
{
    if (GetNvPmApiManager()->Construct(PATH_TO_NVPMAPI_CORE) != S_OK) {
        printf("Failed to load NVPerfSDK.\n");
        return -1;
    }

    if (GetNvPmApi()->Init() != NVPM_OK) {
        printf("Failed to initialize NVPerfSDK.\n");
        return -1;
    }

    HGLRC rcCurrentContext = wglGetCurrentContext();
    if (GetNvPmApi()->CreateContextFromOGLContext((APIContextHandle) rcCurrentContext, &g_hNVPMContext) != NVPM_OK) {
        printf("Failed to create an OpenGL context.\n");
        return -1;
    }

    return 0;
}

static int perfkit_finalize()
{
    if (GetNvPmApi()->DestroyContext(g_hNVPMContext) != NVPM_OK) {
        printf("Failed to destroy the OpenGL context.\n");
        return -1;
    }

    if (GetNvPmApi()->Shutdown() != NVPM_OK) {
        printf("Failed to shutdown NVperfSDK.\n");
        return -1;
    }

    return 0;
}
static NVPMRESULT nvpm_enum_counters_cb(NVPMCounterID id, char *name)
{
    NVPMUINT64 display, type;
    char desc[8192];
    NVPMUINT len;

    /* Get attributes. */
    GetNvPmApi()->GetCounterAttribute(id, NVPMA_COUNTER_DISPLAY, &display);
    GetNvPmApi()->GetCounterAttribute(id, NVPMA_COUNTER_TYPE, &type);

    /* Get decription. */
    GetNvPmApi()->GetCounterDescription(id, desc, &len);

    if (type != NVPM_CT_GPU)
        return NVPM_OK;

    /* Print infos. */
    fprintf(output, "Event #%d\n", id);
    fprintf(output, "name    = %s\n", name);
    fprintf(output, "type    = ");
    switch (type) {
        case NVPM_CT_GPU:
            fprintf(output, "GPU");
            break;
        case NVPM_CT_OGL:
            fprintf(output, "OGL");
            break;
        case NVPM_CT_D3D:
            fprintf(output, "D3D");
            break;
        case NVPM_CT_SIMEXP:
            fprintf(output, "SIMEXP");
            break;
        case NVPM_CT_USER:
            fprintf(output, "USER");
            break;
        default:
            fprintf(output, "UNK");
            break;
    }
    fprintf(output, "\n");
    fprintf(output, "display = ");
    switch (display) {
        case NVPM_CD_RATIO:
            fprintf(output, "RATIO");
            break;
        case NVPM_CD_RAW:
            fprintf(output, "RAW");
            break;
        default:
            fprintf(output, "UNK");
            break;
    }
    fprintf(output, "\n");
    fprintf(output, "desc    = %s\n", desc);
    fprintf(output, "\n");
    return NVPM_OK;
}

static int perfkit_list_events()
{
    output = fopen("perfkit_signals.output", "w+");
    if (!output) {
        printf("Failed to open 'perfkit_signals.output'.\n");
        return -1;
    }

    if (GetNvPmApi()->EnumCountersByContext(g_hNVPMContext, (NVPMEnumFunc)nvpm_enum_counters_cb) != NVPM_OK)
        return -1;

    if (fclose(output) < 0)
        return -1;

    return 0;
}

static int perfkit_do_monitoring(const char *name, uint64_t *value,
                                 uint64_t *cycles)
{
    uint32_t nb_passes;

    if (GetNvPmApi()->BeginExperiment(g_hNVPMContext, &nb_passes) != NVPM_OK) {
        printf("Failed to begin an expriment.\n");
        return -1;
    }

    /* For each passes needed by the selected hardware event. */
    for (uint32_t i = 0; i < nb_passes; i++) {
        if (GetNvPmApi()->BeginPass(g_hNVPMContext, i) != NVPM_OK) {
            printf("Failed to begin the pass %d.\n", i);
            return -1;
        }
        if (GetNvPmApi()->BeginObject(g_hNVPMContext, 0) != NVPM_OK) {
            printf("Failed to begin an object.\n");
            return -1;
        }
        /* Nothing to do here :-). */
        if (GetNvPmApi()->EndObject(g_hNVPMContext, 0) != NVPM_OK) {
            printf("Failed to end an object.\n");
            return -1;
        }
        if (GetNvPmApi()->EndPass(g_hNVPMContext, i) != NVPM_OK) {
            printf("Failed to end the pass %d.\n", i);
            return -1;
        }
    }

    if (GetNvPmApi()->EndExperiment(g_hNVPMContext) != NVPM_OK) {
        printf("Failed to end an expriment.\n");
        return -1;
    }

    /* Poll counter value. */
    if (GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, name,
                                            0, value, cycles) != NVPM_OK) {
        printf("Failed to get counter value.\n");
        return -1;
    }

    return 0;
}

static int perfkit_add_counter(const char *name)
{
    if (GetNvPmApi()->AddCounterByName(g_hNVPMContext, name) != NVPM_OK) {
        printf("Failed to enable counter '%s'.\n", name);
        return -1;
    }
    return 0;
}

/*
static void draw_scene()
{
    int i;

    glClearColor(0.6, 0.6, 0.6, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GetNvPmApi()->BeginObject(g_hNVPMContext, 0);
    for (i = 0; i < 10; i++) {
        glColor3f(0, 1, 1);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f,   1.0f);
        glVertex2f(0.87f,  -0.5f);
        glVertex2f(-0.87f, -0.5f);
        glEnd();
    }
    GetNvPmApi()->EndObject(g_hNVPMContext, 0);

    glFinish();
}

static void render()
{
    NVPMUINT numPasses;

    GetNvPmApi()->BeginExperiment(g_hNVPMContext, &numPasses);
    printf("numPasses=%d\n", numPasses);
    for (NVPMUINT i = 0; i < numPasses; i++) {
        GetNvPmApi()->BeginPass(g_hNVPMContext, i);
        Sleep(1000);
        draw_scene();
        GetNvPmApi()->EndPass(g_hNVPMContext, i);
    }
    GetNvPmApi()->EndExperiment(g_hNVPMContext);

    NVPMUINT64 value, cycles;
    NVPMRESULT ret = GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, pc_name, 0, &value, &cycles);
    if (ret != NVPM_OK) {
        printf("Failed to get counter value\n");
        return;
    }

    glutSwapBuffers();

    if (!value)
        return;

    printf("=================\n");
    printf("ctr=%llu, clk=%llu\n", value, cycles);
    printf("%f\%\n", (double)(value / (float)cycles * 100.0));
}
*/

int main(int argc, char **argv)
{
    const char *event_name = "shader_busy";
    uint32_t nb_poll = 0;
    HANDLE th;

    /* Initialize GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(256, 256);
    glutCreateWindow("GPU Graphics Counters");

    /* Initialize NVPerfSDK. */
    if (perfkit_init() < 0)
        return 1;

    /* Specify the hardware event to monitor. */
    if (perfkit_add_counter(event_name) < 0)
        return 1;

    /* Launch glretrace using a thread and a process. */
    if (run_thread(&th, (LPTHREAD_START_ROUTINE)launch_glretrace))
        return 1;

    while (process_is_running) {
        uint64_t value, cycles;

        if (perfkit_do_monitoring(event_name, &value, &cycles) < 0) {
            /* An error has occured during the monitoring. */
            break;
        }

        if (value > 0) {
            double ratio = (double)(value / (double)cycles * 100.0);

            printf("%d# ctr=%llu, clk=%llu (%0.2f\%)\n",
                   nb_poll, value, cycles, ratio);
           // printf("%f\%\n", (double)(value / (float)cycles * 100.0));
            nb_poll++;
        }
    }

    /* Wait for the thread to terminate. */
    WaitForMultipleObjects(1, &th, TRUE, INFINITE);

    /* Close the thread. */
    CloseHandle(th);

    /* Free resources allocated by NVPerfSDK. */
    if (perfkit_finalize() < 0)
        return 1;

    return 0;

#if 0
    char *filename = "synchro.lock";
    FILE *f = fopen(filename, "w+");
    fclose(f);
#endif

    /* Run GLUT main loop. */
    /*
    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutMainLoop();
    */

    return 0;
}
