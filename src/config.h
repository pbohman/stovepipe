#ifndef CONFIG_H
#define CONFIG_H


// WiFi Credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Prometheus push URL
const char* prompush_url = "https://example.com/prompush/metrics/job/woodstove_job";

/* * CA Certificate: The certificate of the CA that signed your server's cert.
 * This allows the ESP32 to trust the server.
 */
const char* ca_cert  = R"rawliteral(
-----BEGIN CERTIFICATE-----
Paste your CA Certificate here
-----END CERTIFICATE-----
)rawliteral";

/* * Client Certificate: Your device's identity certificate.
 */
const char* client_cert = R"rawliteral(
-----BEGIN CERTIFICATE-----
Paste your Client Certificate here
-----END CERTIFICATE-----
)rawliteral";

/* * Client Private Key: The private key for your device certificate.
 * Keep this secret!
 */
const char* client_key = R"rawliteral(
-----BEGIN PRIVATE KEY-----
Paste your Private Key here
-----END PRIVATE KEY-----
)rawliteral";

#endif
