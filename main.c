//192.168.1.21
#include <mysql.h>
#include <math.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <stdint.h>
#include <unistd.h>
#include <wiringPiI2C.h>
#include <time.h>




#define pumber 22

int main(void)
{
    // ket noi database
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
//172.20.10.2
   char *server = "172.20.10.2";
   char *user = "nt";
   char *password = "132001"; /* set me first */
   char *database = "final";
  wiringPiSetupPhys();
      pinMode(pumber, OUTPUT);
  int fd;
  int a2dChannel = 1; // analog channel
  int a2dVal;
  float a2dVol;
  float Vref = 5;

  if ((fd = wiringPiI2CSetup(0x48)) < 0) {
    printf("wiringPiI2CSetup failed:\n");
  }
while(1)
{
    // Connect to database
    conn = mysql_init(NULL);
    mysql_real_connect(conn,server,user,password,database,0,NULL,0);
    // Read data from manual
    mysql_query(conn, "select * from IoT");
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    int manual = atoi(row[1]);

    if(atoi(row[1]) == 1)
        {
        digitalWrite(pumber, LOW);
        printf("Manual Mode Ocn\n");
        }

    if(atoi(row[1]) == 0)
        {
        digitalWrite(pumber, HIGH);
        printf("Manual Mode On\n");
        }
    if(atoi(row[1]) == 3)
        printf("Manual Mode Close\n");

// read temp from database
mysql_query(conn, "select * from temp");
res = mysql_store_result(conn);
row = mysql_fetch_row(res);
row = mysql_fetch_row(res);
row = mysql_fetch_row(res);
row = mysql_fetch_row(res);

float tempIn = atof(row[2]);
printf("%f\n",tempIn);
 
 // read data from sensor
    wiringPiI2CWrite(fd,0x40 | a2dChannel);

     a2dVal = wiringPiI2CRead(fd);
     a2dVol = a2dVal * Vref / 255;
     int doAm = (255-a2dVal)*100/255;
    printf("Do am= %d%% \n" ,doAm);

   mysql_query(conn, "select * from auto");
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    int solid = atoi(row[1]);
    int tempOut  = atoi(row[2]);
    // char * timeSet = row[3];
    char * timeSet = row[3];
    int timeHour = atoi(row[4]);
    int timeMinute = atoi(row[5]);
    int timeSecond = atoi(row[6]);

    if(solid != 0 && tempOut==0)
    {
    printf("SOLID SETUP RUNNING\n");
    printf("SOLID SETUP VALUE: %d\n",solid);
    {
    if(doAm > solid)
        digitalWrite(pumber, HIGH);
    if(doAm < solid)
        digitalWrite(pumber, LOW);
        
    }
    }
    if(solid == 0)
     printf("SOLID SETUP CLOSE\n");

    if(tempOut != 0 && solid ==0)
    {
    printf("TEMP SETUP RUNNING\n");
    printf("TEMP SETUP VALUE: %d\n", tempOut);
        {
            if(tempIn < tempOut)
                digitalWrite(pumber, LOW);
            if(tempIn > tempOut)
                digitalWrite(pumber, HIGH);
        }
    }
    if(tempOut == 0)
     printf("TEMP SETUP CLOSE\n");




    // read time
    time_t T = time(NULL);
    struct tm tm = *localtime(&T);
    printf("%02d\n",timeHour);
    printf("%02d\n",timeMinute);
    printf("%02d\n",timeSecond);
    printf("%02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    if(manual ==3)
    {
    if(tempOut ==0 && solid==0)
    {
        printf("DATE MODE RUNNING\n");
        if(timeHour == tm.tm_hour && timeMinute == tm.tm_min )
            digitalWrite(pumber, LOW);
        
        else
            digitalWrite(pumber, HIGH);
    }
    if(tempOut !=0 | solid !=0)
    printf("DATE MODE CLOSE\n\n");
    }


    char sql[200];
    sprintf(sql,"insert into temp set solid =%d", doAm);
    mysql_query(conn, sql);
    
    
    mysql_close(conn);

    delay(1000);

    }


    
    // clear result and close the connection
    

return 0;
}








