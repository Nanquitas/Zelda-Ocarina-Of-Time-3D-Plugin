#!/usr/bin/env Python

import sys
import ftplib
import datetime
from ftplib import FTP

# Usage:
# sendfile.py "filename" "ftppath" "host" "ip"

def printf(string):
	print(datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d %H:%M:%S') + " : " + string);

def checkfolder(ftp):
	files = []

	try:
		files = ftp.nlst()
	except ftplib.error_perm, resp:
		if str(resp) != "550 No files found":
			printf("Couldn't retrieve file list")
		else:
			return
	
	for f in files:
		if (".plg" in f or "CTRPFData.bin" in f):
			parts = f.split()
			name = parts[len(parts) - 1]
			printf("Deleting " + name)
			try:
				ftp.delete(name)
				printf(name + " was successfully deleted")
			except Exception:
				printf("An error occured")
				continue

def cdTree(ftp, currentDir):
	if currentDir != "":
		try:
			ftp.cwd(currentDir)
		except IOError:
			cdTree("/".join(currentDir.split("/")[:-1]))
			ftp.mkd(currentDir)
			ftp.cwd(currentDir)
		except:
			print "Unexpected error:", sys.exc_info()[0]
			raise


def sendPlugin(ftp, path, name, file):
	printf("Moving to: ftp:/" + path);
	#try:
	cdTree(ftp, path)
	#except Exception:
	#	pass

	checkfolder(ftp)

	try:        
		printf("Sending " + name + " to ftp:" + ftp.pwd())
		ftp.storbinary('STOR '+ name, file);
		file.seek(0, 0)
		printf("Done\n")
	except Exception:
		printf("/!\ An error occured. /!\ ");

if __name__ == '__main__':
	print("");
	printf("FTP File Sender\n")
	try:
		filename = sys.argv[1]
		lumaname = 'plugin.plg'
		lumapath = '/luma/plugins/' + sys.argv[2]
		ntrpath = '/plugin/' + sys.argv[2]
		host = sys.argv[3]
		port = sys.argv[4]

		ftp = FTP()
		printf("Connecting to " + host + ":" + port);
		ftp.connect(host, port);
		printf("Connected");

		printf("Opening " + filename);
		file = open(sys.argv[1], "rb");
		printf("Success");

	except IOError as e:
		printf("/!\ An error occured. /!\ ");

	sendPlugin(ftp, ntrpath, filename, file)
	sendPlugin(ftp, lumapath, lumaname, file)
		
	file.close();

	ftp.quit();
	printf("Disconnected");
