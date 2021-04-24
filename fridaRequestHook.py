import frida, sys

def on_message(message, data):
    print("[%s] => %s" % (message, data))

session = None
while session == None:
    try:
        session = frida.attach("trove.exe")
    except frida.ProcessNotFoundError:
        print("Waiting for process trove.exe")


script = session.create_script("""

    var baseAddr = Module.findBaseAddress('trove.exe');
    console.log('Trove.exe baseAddr: ' + baseAddr);
    var methodAddr = baseAddr.add(0x9691a0);
    console.log('SendRequest at: ' + methodAddr);

    // Hook the addr
    Interceptor.attach(methodAddr, {

        // When function is called, print out its parameters
        onEnter: function (args) {
            if (args[4].equals(Module.findBaseAddress('trove.exe').add(0xfa4f18).readPointer()))
            {
                console.log(args[-1]);
            console.log(args[-1].readPointer().readCString());
            console.log(args[-2]);
            console.log(args[-2].readPointer().readCString());
            console.log(args[-4]);
            console.log(args[-4].readPointer().readCString());
            console.log('[+] Called SendRequest');
            for (var i = 0; i < 20; i++)
            {
                console.log('[+] '+i+': ' + args[i]);
            }
            //console.log('[+] 0: ' + args[0]);
            //console.log('[+] 1: ' + args[1]);
            //console.log('[+] 2: ' + args[2]);
            //console.log('[+] 3: ' + args[3]);
            //console.log('[+] 4: ' + args[4]);
            //console.log('[+] 5: ' + args[5]);
            //console.log('[+] 6: ' + args[6]);
            //console.log('[+] 7: ' + args[7]);
            //console.log(this.context.eax)
            //console.log(this.context.ebp.add(-0x8).readPointer().readCString())
            console.log(this.context.ebp.add(0x8))
            console.log(this.context.ebp.add(0x8).readPointer())
            console.log(this.context.ebp.add(0x8).readPointer().readCString())
            //console.log(this.context.ebp.add(0x8).readPointer().readPointer())
            //console.log(this.context.esp.add(0x8).readPointer().readPointer().readCString())
            //console.log(this.context.ebp.add(0xC).readPointer().readCString())
            
            console.log('this  : ' + JSON.stringify(this));
            console.log('Context  : ' + JSON.stringify(this.context));
            console.log('');
            }
            //console.log(args[0].readPointer().readCString())
            //this.outptr = args[2];
            //this.outsize = args[3].toInt32();
        },

        /*onLeave: function (retval) {
            dumpAddr('Output', this.outptr, this.outsize);
            console.log('[+] Returned from SetAesDeCrypt0: ' + retval);
        }*/
    });

    """)
script.on('message', on_message)
script.load()
while True:
    line = sys.stdin.readline()
    if "exit" in line:
        session.detach()
        sys.exit(0)

print(session)