
char strM[13] = {'M', 'B', 'T', 'p', '<', 'M', 'e', 'a', 's', 'u', 'r', 'e', '>'};
char strC[13] = {'C', 'B', 'T', 'p', '<', 'C', 'o', 'm', 'p', 'u', 't', 'e', '>'};
char inbyte;
char measureIn[12];
char computeIn[15];
char statusIn[5];
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    Serial1.begin(9600);
}

void loop() {
    measureSC();
    //delay(1000);
    computeSC();
    //delay(1000);
    statusSC();
    Serial.println();
    delay(1000);
    
}


void communication(char* str) {
    Serial1.print(str); 
    Serial1.flush();

    if (str[0] == 'M') {
        while ((Serial.available() < 10)) {
            
        }
        Serial.readBytes(measureIn, 10);
        Serial.print(measureIn);
        
        // print input chars one by one
        /*
        while (Serial.available() > 0) {
            inbyte = Serial.read();
            Serial.print(inbyte);
            Serial.print(" ");
        } 
        */
        Serial.println();
    }
    else if (str[0] =='C') {
        while ((Serial.available() < 13)) {
            
        }
        
        Serial.readBytes(computeIn, 13);
        Serial.print(computeIn);

        /*
        while (Serial.available() > 0) {
            inbyte = Serial.read();
            Serial.print(inbyte);
            Serial.print(" ");
        } 
        */
        Serial.println();
    }
    else if (str[0] == 'S') {
        while (Serial.available() < 3) {
            
        }
        
        Serial.readBytes(statusIn, 3);
        Serial.print(statusIn);

        /*
        while (Serial.available() > 0) {
            inbyte = Serial.read();
            Serial.print(inbyte);
            Serial.print(" ");
        } 
        */
        Serial.println();
    }
}

void measureSC() {
    char str[13];
    str[0] = 'M';
    str[1] = 'B';
    str[2] = 'T';
    str[3] = 'P';
    str[4] = '<';
    str[5] = 'M';
    str[6] = 'e';
    str[7] = 'a';
    str[8] = 's';
    str[9] = 'u';
    str[10] = 'r';
    str[11] = 'e';
    str[12] = '>';

    communication(str);
}

void computeSC() {
    char str[13];
    str[0] = 'C';
    str[1] = 'B';
    str[2] = 'T';
    str[3] = 'P';
    str[4] = '<';
    str[5] = 'C';
    str[6] = 'o';
    str[7] = 'm';
    str[8] = 'p';
    str[9] = 'u';
    str[10] = 't';
    str[11] = 'e';
    str[12] = '>';
    communication(str);
}

void statusSC() {
    char str[13];
    str[0] = 'S';
    str[1] = 'A';
    str[2] = 'A';
    str[3] = 'A';
    str[4] = '<';
    str[5] = 'B';
    str[6] = 'a';
    str[7] = 't';
    str[8] = 'S';
    str[9] = 't';
    str[10] = 'a';
    str[11] = 't';
    str[12] = '>';
    communication(str);
}

