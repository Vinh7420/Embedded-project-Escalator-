#include <systemc.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace sc_core;
using namespace std;

class Info
{
private:
    bool ppl_in, ppl_out, over_weight_sensor, alert_sensor;

public:
    Info(){};
    Info(bool ppl_in,bool ppl_out, bool over_weight_sensor,bool alert_sensor)
    {
        this->ppl_in = ppl_in;
        this->ppl_out = ppl_out;
        this->over_weight_sensor = over_weight_sensor;
        this->alert_sensor = alert_sensor;
    }

    void setppl_in(bool ppl_in)
    {
        this->ppl_in = ppl_in;
    }

    void setppl_out(bool ppl_out)
    {
        this->ppl_out = ppl_out;
    }

    void setover_weight_sensor(bool over_weight_sensor)
    {
        this->over_weight_sensor = over_weight_sensor;
    }
    void setalert_sensor(bool alert_sensor)
    {
        this->alert_sensor = alert_sensor;
    }

    bool setpppl_in()
    {
        return this->ppl_in;
    }
    bool getpp_out()
    {
        return this->ppl_out;
    }
    bool getover_weight_sensor()
    {
        return this->over_weight_sensor;
    }
    bool getalert_sensor()
    {
        return this->alert_sensor;
    }
};
SC_MODULE(Escalator)
{
    int a;
    int ppl_nums = 0;
    sc_in<bool> ppl_in;
    sc_in<bool> ppl_out;
    sc_out<bool> move;
    sc_out<bool> stop;
    sc_out<bool> led_on;
    sc_out<bool> led_off;

    void escalator_system(){
        while(true){
        if(move == 1){
        cout << "\n Thang cuon dang hoat dong";
        }else{
        cout << "\n Thang cuon da dung ";
        }
        cout << "\n \n Chon truong hop: \n 1.Co nguoi vao thang. \n 2. Co nguoi ra khoi thang ";
        cin>>a;
        switch(a){
            case 1:
            ppl_nums += 1;
            if(ppl_nums !=0){
                move.write(1);
                led_on.write(1);
                led_off.write(0);
                cout << " \n So luong nguoi:" << ppl_nums;
                break;
            }
            case 2:
            if(ppl_nums > 0){
                ppl_nums -=1;
                if(ppl_nums==0){
                    move.write(0);
                    led_on.write(0);
                    led_off.write(1);
                    cout << " \n Thang cuon dang da dung \n";
                    exit(0);
                }
            }
        }
        wait(3, SC_SEC);
    }
}
    SC_CTOR(Escalator){
        SC_THREAD(escalator_system);
        sensitive << ppl_in;
        sensitive << ppl_out;
    }
};

SC_MODULE(Software){
    sc_in<bool> over_weight_sensor;
    sc_in<bool> alert_sensor;
    sc_out<bool> over_weight;
    sc_out<bool> alert;
    void Alert(){
        while(true){
            over_weight.write(rand()%2 ==1);
            alert.write(rand()%2 == 1);
        if(over_weight.read() == 1){
            cout << "\n Qua tai";
            cout << "\n Thang cuon dung hoat dong. \n";
            exit(0);
        }
        else if(alert.read()==1){
            cout << " \n Canh bao nguy hiem";
            cout << "\n Thang cuon dung hoat dong. \n";
            exit(0);
        }
        wait(3, SC_SEC);
    }
}
    SC_CTOR(Software){
        SC_THREAD(Alert);
        sensitive << over_weight_sensor;
        sensitive << alert_sensor;
    }
};
int sc_main(int argc, char *argv[])
{
    sc_signal<bool> move;
    sc_signal<bool> stop;
    sc_signal<bool> over_weight;
    sc_signal<bool> alert;
    sc_signal<bool> led_on;
    sc_signal<bool> led_off;
    sc_signal<bool> ppl_in;
    sc_signal<bool> ppl_out;
    sc_signal<bool> over_weight_sensor;
    sc_signal<bool> alert_sensor;

    Escalator escalator("esc");
    escalator.ppl_in(ppl_in);
    escalator.ppl_out(ppl_out);
    escalator.move(move);
    escalator.stop(stop);
    escalator.led_on(led_on);
    escalator.led_off(led_off);

    Software software("soft");
    software.over_weight_sensor(over_weight_sensor);
    software.over_weight(over_weight);
    software.alert_sensor(alert_sensor);
    software.alert(alert);

    sc_start(100, SC_SEC);
    return 0;
}