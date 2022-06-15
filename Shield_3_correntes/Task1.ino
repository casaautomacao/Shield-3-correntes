

void Task1code( void * pvParameters ) {

      for(;;) {
        
          Irms1 = emon1.calcIrms(200);  // Calculate Irms only
          Irms2 = emon2.calcIrms(200);
          Irms3 = emon3.calcIrms(200);
      }
      
}
