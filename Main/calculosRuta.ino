
void ruta(){
  distanciaObjetivo(latitud, longitud, latitudObjetivo, longitudObjetivo);
  headingObjetivo = headingObjective(latitud, longitud, latitudObjetivo, longitudObjetivo);
}

float headingObjective(float lat1, float lon1, float lat2, float lon2) { 
  
  // Calculamos la diferencia entre las coordenadas
  float dLat = lat2 - lat1;
  float dLon = lon2 - lon1;
  
  // Calculamos el heading utilizando la fórmula de la dirección inicial
  float y = sin(dLon) * cos(lat2);
  float x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dLon);
  
  float h = atan2(y, x) * 180 / PI;
  
  if (h < 0) {
    return h += 360;
  }
  
  return h;
}

float distanciaObjetivo(float lat1, float lon1, float lat2, float lon2) { 
  
  // Radio de la Tierra en metros
  const float R = 6371000;

  // Convertimos las coordenadas a radianes
  lat1 = lat1 * PI / 180;
  lon1 = lon1 * PI / 180;
  lat2 = lat2 * PI / 180;
  lon2 = lon2 * PI / 180;

  // Calculamos la diferencia entre las coordenadas
  float dLat = lat2 - lat1;
  float dLon = lon2 - lon1;

  // Aplicamos la fórmula de Haversine
  float a = sin(dLat/2) * sin(dLat/2) + cos(lat1) * cos(lat2) * sin(dLon/2) * sin(dLon/2);
  float c = 2 * atan2(sqrt(a), sqrt(1-a));
  float d = R * c;

  return d; //Mandamos la distancia de regreso
  
}
