
void elevationCheck() {
  
  if (alturaRelativa + 3 > alturaMaxima && banderaElevacionPositiva == false && banderaAterrizaje == false) {
    alturaMaxima = alturaRelativa;
    contadorAscenso++;
    if (contadorAscenso > 4){
    banderaElevacionPositiva = true;
    alturaMaxima = alturaRelativa;}
  }

  if (banderaElevacionPositiva == true && alturaRelativa < alturaMaxima - 3 && banderaElevacionNegativa == false && banderaAterrizaje == false) {
    contadorDescenso++;
    alturaMaxima = alturaRelativa;
    if (contadorDescenso > 4){
      banderaElevacionNegativa = true; 
    }
  }

  if (banderaElevacionPositiva == true && banderaElevacionNegativa == true && alturaRelativa < 0.0 + 4 && alturaRelativa > 0.0 - 4 && banderaAterrizaje == false){
    banderaAterrizaje = true;
  }

  if (banderaAterrizaje == true && banderaMovimiento == false) {
    banderaMovimiento == true;
    delay(10000);
  }

}
