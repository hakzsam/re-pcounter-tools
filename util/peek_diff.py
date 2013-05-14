#!/usr/bin/python2

import sys
import subprocess
import getopt

start_color = "[0;31m"
stop_color = "[0m"

def usage():
	print "Usage: %s [-c chipset] [-s restrict_start -e restrict_end] peek1 peek2\n" % sys.argv[0]
	exit(-1)

def lookup(chipset, reg, value):
	try:
		p = subprocess.Popen(['lookup', '-a', chipset, "%x" % reg, "%x" % value], shell=False, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		(stdout, stderr) = p.communicate()
		return stdout if p.returncode == 0 else ""
	except:
		return "lookup not found"

def get_get_reglist(filename, reg_start, reg_end):
	file = open(filename, "r")
	lines = file.readlines()
	file.close()

	cur_base = 0
	cur_range = 0
	cur_pos = 0
	regs = dict()

	for line in lines:
		if (line.startswith("<dump")):
			# finish the current range by adding 0s
			for i in range(cur_pos, cur_base+cur_range, 4):
				if (i >= reg_start and i <= reg_end):
					regs[i] = 0
			fields = line.split()
			cur_base = int(fields[1], 16)
			cur_range = int(fields[2].split('>')[0], 16)
			cur_pos = cur_base
		elif (line.find(":") != -1):
			fields = line.split()
			new_pos = int(fields[0].split(':')[0], 16)
			# set the missing regs to 0
			for i in range(cur_pos, new_pos, 4):
				if (i >= reg_start and i <= reg_end):
					regs[i] = 0
			#set the new values
			max = ((cur_base+cur_range)-new_pos)/4
			for i in range(0, 4 if max > 4 else max):
				cur_pos = new_pos+i*4
				if (cur_pos >= reg_start and cur_pos <= reg_end):
					regs[cur_pos] = int(fields[i+1], 16)
			cur_pos += 4
	return regs

exclude_regs = [ 0x1094, 0x1578, 0x100210, 0x1008e0, 0x100c80, 0x100c08, 0x100b74]
def reg_is_blacklisted(reg):
	if (reg in exclude_regs) or (reg >= 0x1300 and reg <= 0x1500):
		return True
	else:
		return False

def reg_list_diff(reglist1, reglist2):
	diff = []
	for r in reglist1.iterkeys():
		try:
			if reglist1[r] != reglist2[r] and (not reg_is_blacklisted(r)):
				diff.append((r, reglist1[r], reglist2[r]))
		except:
			continue
	return diff

def reg_print_diff(diff, chipset):
	for (r, v1_i, v2_i) in sorted(diff):
		v1="%.8x" % v1_i
		v2="%.8x" % v2_i
		v1_c = v2_c = ""
		color = False
		for i in range(0, len(v1)):
			if color:
				if (v1[i] == v2[i]):
					v1_c += stop_color
					v2_c += stop_color
					color = False
			else:
				if (v1[i] != v2[i]):
					v1_c += start_color
					v2_c += start_color
					color = True

			v1_c += v1[i]
			v2_c += v2[i]
		if color:
			v1_c += stop_color
			v2_c += stop_color
		if chipset != "":
			print "%.8x: %s -> %s: (%s) --> (%s)" % (r, v1_c, v2_c, lookup(chipset, r, v1_i).strip(), lookup(chipset, r, v2_i).strip())
		else:
			print "%.8x: %s -> %s" % (r, v1_c, v2_c)

def main():
	# main program
	try:
		opts, args = getopt.getopt(sys.argv[1:], "c:a:s:e:", ["chipset", "architecture=", "start=", "end="])
	except getopt.GetoptError, err:
		# print help information and exit:
		print str(err) # will print something like "option -a not recognized"
		usage()
		sys.exit(2)

	reg_start = 0x0
	reg_end = 0xffffffff
	chipset = "NV86"
	for o, a in opts:
		if o in ("-s", "--start"):
			reg_start = int(a, 16)
		elif o in ("-e", "--end"):
			reg_end = int(a, 16)
		elif o in ("-c", "--chipset", "-a", "--architecture"):
			chipset = a
		else:
			assert False, "unhandled option"

	if (len(sys.argv) < 3):
		usage()

	reglist1 = get_get_reglist(args[0], reg_start, reg_end)
	reglist2 = get_get_reglist(args[1], reg_start, reg_end)
	diff = reg_list_diff(reglist1, reglist2)
	reg_print_diff(diff, chipset)

if __name__ == "__main__":
    main()
