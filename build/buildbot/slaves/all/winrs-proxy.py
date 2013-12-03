#!/usr/bin/env python
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
import sys,socket,os,getopt,time

host=''
port=0
if os.environ.has_key("WINRSSERVERHOST"):
    host=os.environ.get("WINRSSERVERHOST")
if os.environ.has_key("WINRSSERVERPORT"):
    port=int(os.environ.get("WINRSSERVERPORT"))
expectNoOutput=os.environ.get("WINRSSERVEREXPECTNOOUTPUT", False)

timeout=-1
winrs_host=''
winrs_user=''
winrs_pass=''

usage='''
winrs.py args ...
--port=
--timeout=
--host=
--cmd=
--file=
--skipExit
'''
cmd='winrs '
longoptions=['port=','host=','cmd=','timeout=','file=','skipexit']
skipExit=False
infile=None

cmd="winrs %s" % ' '.join(sys.argv[1:])

if host=='':
   print("must specify host through --host or environment variable WINRSSERVERHOST")
   sys.exit(1)

if port==0:
   print("must specify port through --port or environment variable WINRSSERVERPORT")
   sys.exit(1)


def run():
    start=time.time()
    s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.connect((host,port))
    except:
        print("could not connect to host=%s port=%s" % (host,port))
        sys.exit(1)

    s.send("set timeout -1\n")
    start=time.time()
    result=''
    while True:
        result+=s.recv(1024)
        if result.find('$'):
            break
        if time.time()-start>30:
            print("error failed to set timeout")
            sys.exit(1)
        time.sleep(.5)


    if infile!=None:
        lines=open(infile)
        count=0
        for line in lines:
            if line=='':
                continue
            s.send(line+'\n')
            result=s.recv(1024)
            if result.find("finished")==-1:
                print("error: did not receive ack")
                break
            print('[%d] %s' % (count,line))
            count+=1
        print("done sending file")
    else:
        s.send(cmd+'\n')
    result=''
    exitSent=False
    while True:
        result+=s.recv(1024)
        if result.find('$') and exitSent==False:
            exitSent=True
            s.send('exit\n')
            if skipExit:
                break
        if result.find('closing connection')>-1:
            break
        if timeout!=-1 and time.time()-start>timeout:
            result+='timed out after %d' % timeout
            break
        time.sleep(.5)
    s.close()
    if skipExit:
        code=0
    else:
        fnd=result.find('closing connection')
        code=1
        if fnd>-1:
            result=result[0:fnd-3]
            code=0

    return result, code


tries=5
attempts=0
output=""
code=0
while (attempts < tries):
    #print(":: Attempt %s" %attempts)
    output,code = run()
    #print(":: len(output) %s" % len(output))
    #print(output)
    if len(output) != 0 or expectNoOutput:
        break
    attempts+=1

print(output)
#print("exitcode=%d" % code)
sys.exit(code)


