#!/usr/bin/env python3
#
# run environment: unix
#
# maintainer: lb

import os
import sys
import argparse

parser = argparse.ArgumentParser(description='Run all testcases with golden and your executables')
parser.add_argument('--test', dest='testExeName', nargs=None, default='CMP',
                    help='Your CMP executable filename, default "CMP"')
parser.add_argument('--golden', dest='goldenExeName', nargs=None, default='CMP_golden',
                    help='Golden CMP executable filename, default "CMP_golden"')
parser.add_argument('--testfolder', dest='testfolder', nargs=None, default='testcases',
                    help='Testcases root folder, default "testcases"')
parser.add_argument('parameters', nargs='*', help='CMP parameters, leave empty for default')

args = parser.parse_args()

if len(args.parameters) != 0 and len(args.parameters) != 10:
    print('invalid parameter, number of parameter should be either 0 or 10')
    sys.exit(1)

testExeName = args.testExeName
goldenExeName = args.goldenExeName
testfolder = args.testfolder

print('check golden executable "' + goldenExeName + '"...', end='')
if os.path.isfile(goldenExeName):
    print(' exists')
else:
    print(' not found')
    sys.exit(1)

print('check test executable "' + testExeName + '"...', end='')
if os.path.isfile(testExeName):
    print(' exists')
else:
    print(' not found')
    sys.exit(1)

print('check testcase root folder "' + testfolder + '"...', end='')
if os.path.isdir(testfolder):
    print(' exists')
else:
    print(' not found')
    sys.exit(1)

for root, dirs, files in os.walk(testfolder):
    for path in sorted(dirs):
        if path != '.' and path != '..':
            os.chdir(os.path.join(root, path))
            print('Enter ' + os.getcwd())
            os.system('cp ../../' + goldenExeName + ' ./ -f')
            os.system('cp ../../' + testExeName + ' ./ -f')
            goldenRunCommand = './' + goldenExeName
            testRunCommand = './' + testExeName
            if len(args.parameters) != 0:
                for param in args.parameters:
                    goldenRunCommand = goldenRunCommand + ' ' + str(param)
                    testRunCommand = testRunCommand + ' ' + str(param)
            print('Run ' + testRunCommand)
            chk_yours = os.system(testRunCommand + ' > temp_de0x882749.txt')
            os.rename('snapshot.rpt', 'ssnapshot.rpt')
            os.rename('report.rpt', 'rreport.rpt')
            print('Run ' + goldenRunCommand)
            chk_golden = os.system(goldenRunCommand + ' > temp_de0x882749.txt')
            os.system('rm -f ./temp_de0x882749.txt')
            os.system('rm -f ' + goldenExeName)
            os.system('rm -f ' + testExeName)
            os.system('diff snapshot.rpt ssnapshot.rpt')
            os.system('diff report.rpt rreport.rpt')
            print('Leave ' + os.getcwd())
            os.chdir('../../')

