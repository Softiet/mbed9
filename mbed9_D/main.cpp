#include "mbed.h"
#include "mbed_rpc.h"

/**
 *  This example program has been updated to use the RPC implementation in the new mbed libraries.
 *  This example demonstrates using RPC over serial
**/

DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);

Serial pc(USBTX, USBRX);

void LEDControl(Arguments *in, Reply *out);
RPCFunction rpcLED(&LEDControl, "LEDControl");
double x, y;

Ticker led1_tick;
Ticker led2_tick;


bool led1_status = False;
void blink1();

//void blink2();

int main() {
    //The mbed RPC classes are now wrapped to create an RPC enabled version - see RpcClasses.h so don't add to base class
    // receive commands, and send back the responses
    char buf[256], outbuf[256];
    while(1) {
        memset(buf, 0, 256);
        for (int i = 0; ; i++) {
            char recv = pc.getc();
            if (recv == '\r') {
                pc.printf("\r\n");
                break;
            }
            buf[i] = pc.putc(recv);
        }

        //Call the static call method on the RPC class
        RPC::call(buf, outbuf);
        pc.printf("%s\r\n", outbuf);
    }
}


// Make sure the method takes in Arguments and Reply objects.

void LEDControl (Arguments *in, Reply *out)   {
    bool success = true;

    // In this scenario, when using RPC delimit the two arguments with a space.
    x = in->getArg<double>();
    y = in->getArg<double>();
    // Have code here to call another RPC function to wake up specific led or close it.
    char buffer[200], outbuf[256];
    char strings[20];
    int led = x;
    int blink_on = y;
    /*
    int n = sprintf(strings, "/myled%d/write %d", led, on);
    strcpy(buffer, strings);
    RPC::call(buffer, outbuf);
    */
    if( led == 0){
        if(blink_on == 1){
            led1_tick.attach(&blink1,0.2);
        }
        else{

        }
    }
    else{
        out->putData("Input strange led number. Fxck off!")
    }

    if (success) {
        out->putData(buffer);
    }
    else {
        out->putData("Failed to execute LED control.");
    }
}





void blink1(){
    led1_status = ~led1_status;
    int n = sprintf(strings, "/myled%d/write %d", 1, led1_status);
    strcpy(buffer, strings);
    RPC::call(buffer, outbuf);
}


int main(){

    time_up.attach( &blink, 0.2 );

    while(1);

}