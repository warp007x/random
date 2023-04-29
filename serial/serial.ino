const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;

int ch1,ch2,ch3,ch4;

void setup()
{
   Serial.begin(115200);
   Serial.setTimeout(100);
   Serial.println("<Arduino is ready>  Enter CH1,CH2,CH3,CH4 seperated with a comma (,) ");
}

void loop()
{
   recvWithEndMarker();
//   showNewData();
   if (newData)
   {
      parseData();
   }
}

void recvWithEndMarker()
{
   static byte ndx = 0;
   char endMarker = '\n';
   char rc;

   while (Serial.available() > 0 && newData == false)
   {
      rc = Serial.read();

      if (rc != endMarker)
      {
         receivedChars[ndx] = rc;
         ndx++;
         if (ndx >= numChars)
         {
            ndx = numChars - 1;
         }
      }
      else
      {
         receivedChars[ndx] = '\0'; // terminate the string
         ndx = 0;
         newData = true;
      }
   }
}

void showNewData()
{
   if (newData == true)
   {
      Serial.print("This just in ... ");
      Serial.println(receivedChars);
      //newData = false;
   }
}

void parseData()
{
   char *strings[16]; // an array of pointers to the pieces of the above array after strtok()
   char *ptr = NULL; byte index = 0;
   ptr = strtok(receivedChars, ",");  // delimiters, comma
   while (ptr != NULL)
   {
      strings[index] = ptr;
      index++;
      ptr = strtok(NULL, ",");
   }
   //Serial.println(index);
   // print all the parts
   //Serial.println("The Pieces separated by strtok()");
//   for (int n = 0; n < index; n++)
//   {
//      //Serial.print("piece ");
//      //Serial.print(n);
//      //Serial.print(" = ");
//      Serial.println(strings[n]);
//   }
   // convert string data to integer numbers
   ch1 = atof(strings[0]);
   ch2 = atof(strings[1]);
   ch3 = atof(strings[2]);
   ch4 = atof(strings[3]);
   newData = false;

   Serial.print("CH1=");
   Serial.print(ch1, DEC);
   Serial.print(":CH2=");
   Serial.print(ch2, DEC);
   Serial.print(":CH3=");
   Serial.print(ch3, DEC);
   Serial.print(":CH4=");
   Serial.print(ch4, DEC);
   Serial.println(); // blank line
}
