/*
  Práctica 2.3 Biosfera (Litosfera): Monitor de humedad del suelo
  Desarrollo Sustentable - Unidad 2: Escenario natural
  Tecnológico Nacional de México, campus Mazatlán
  Alumno: Christian Paul Lizárraga Oronia
  Placa: Arduino UNO R4 WiFi

  Conexiones:
    Sensor VCC -> 5V
    Sensor GND -> GND
    Sensor SIG -> A0
    LED (+)    -> resistencia 220 ohms -> pin 13
    LED (-)    -> GND

  Funcionamiento:
    - Lee la señal analógica del sensor (0 a 1023).
    - Convierte la lectura a porcentaje de humedad con un mapeo invertido
      (lectura alta = suelo seco = 0 %, lectura baja = suelo mojado = 100 %).
    - Si la humedad es menor al umbral: TIERRA SECA -> LED apagado.
    - Si la humedad es mayor o igual al umbral: TIERRA HUMEDA -> LED encendido.
*/

const int PIN_SENSOR = A0;   // Señal del sensor
const int LED_PIN    = 13;   // LED indicador

// Porcentaje mínimo de humedad para considerar la tierra húmeda
const int UMBRAL_PORCENTAJE = 40;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("=== Monitor de humedad del suelo ===");
}

void loop() {
  int lectura = analogRead(PIN_SENSOR);

  // Mapeo invertido: lectura alta (seco) = 0%, lectura baja (mojado) = 100%
  int porcentaje = map(lectura, 1023, 0, 0, 100);
  porcentaje = constrain(porcentaje, 0, 100);

  Serial.print("Lectura: ");
  Serial.print(lectura);
  Serial.print("  |  Humedad: ");
  Serial.print(porcentaje);
  Serial.print("%  |  Estado: ");

  // Poca humedad -> TIERRA SECA -> APAGA LED
  if (porcentaje < UMBRAL_PORCENTAJE) {
    Serial.println("TIERRA SECA -> Se recomienda regar");
    digitalWrite(LED_PIN, LOW);   // LED apagado
  }
  // Suficiente humedad -> TIERRA HUMEDA -> ENCIENDE LED
  else {
    Serial.println("TIERRA HUMEDA -> No necesita riego");
    digitalWrite(LED_PIN, HIGH);  // LED encendido
  }

  delay(1000);  // Una lectura por segundo
}
