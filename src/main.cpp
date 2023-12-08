#include <Arduino.h>
#include <WiFi.h>
#include <data/Pins.cpp>
#include <data/Stats.cpp>
#include <modules/Car.cpp>
#include <modules/Server.cpp>

Wheel frontLeftWheel;
Wheel frontRightWheel;
Wheel rearLeftWheel;
Wheel rearRightWheel;

Car car;
CarServer stats;

// const char *ssid = "Wifi2Fast4U";
// const char *password = "un_ennemi_dead";
// const bool isAp = true;

const char *ssid = "SelfOne";
const char *password = "jeannelpb";
const bool isAp = false;

WiFiServer server(80);

unsigned long currentTime = millis();
unsigned long previousTime = 0;

const long timeoutTime = 2000;

void setup()
{
    Serial.begin(9600);
    Serial.println("Greetings! I'm Carbot, delighted to be in your orbit. Cheers to the pleasure of our rendezvous, old chap!");

    frontLeftWheel = Wheel(
        FRONT_LEFT_WHEEL_PWM,
        FRONT_LEFT_WHEEL_FWD,
        FRONT_LEFT_WHEEL_BCK);

    frontRightWheel = Wheel(
        FRONT_RIGHT_WHEEL_PWM,
        FRONT_RIGHT_WHEEL_FWD,
        FRONT_RIGHT_WHEEL_BCK);

    rearLeftWheel = Wheel(
        REAR_LEFT_WHEEL_PWM,
        REAR_LEFT_WHEEL_FWD,
        REAR_LEFT_WHEEL_BCK);

    rearRightWheel = Wheel(
        REAR_RIGHT_WHEEL_PWM,
        REAR_RIGHT_WHEEL_FWD,
        REAR_RIGHT_WHEEL_BCK);

    car = Car(
        frontLeftWheel,
        frontRightWheel,
        rearLeftWheel,
        rearRightWheel);

    stats = CarServer(12);
    stats.setStat(0, 'D'); // set STATUS to Disabled

    if (isAp)
    {
        Serial.println("Hoi fam! Creating a access point...");
        WiFi.mode(WIFI_AP);

        IPAddress ip(192, 168, 43, 1);
        IPAddress gateway(192, 168, 43, 1);
        IPAddress subnet(255, 255, 255, 0);
        WiFi.softAPConfig(ip, gateway, subnet);

        WiFi.softAP(ssid, password);
        Serial.print("Here is my address bruv: ");
        Serial.println(WiFi.softAPIP());
    }
    else
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);

        Serial.print("Mode set to STA (station), connecting to ");
        Serial.println(ssid);

        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.print(".");
            delay(300);
        }

        Serial.println("\n");
        Serial.println("Hoi fam, I'm connected to the network mate!");
        Serial.print("Here is my IP address bruv: ");
        Serial.println(WiFi.localIP());
    }

    server.begin();
    Serial.println("Okay mate, I'm ready to receive your orders!");
}

void loop()
{
    WiFiClient client = server.available();

    if (client)
    {
        currentTime = millis();
        previousTime = currentTime;

        String header = "";
        String currentLine = "";
        while (client.connected() && currentTime - previousTime <= timeoutTime)
        {
            currentTime = millis();
            if (client.available())
            {
                char c = client.read();
                Serial.write(c);
                header += c;

                if (c == '\n')
                {
                    if (currentLine.length() == 0)
                    {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        // Parse GET /status
                        if (header.startsWith("GET /status"))
                        {
                            Serial.println("[GET] /status");
                            Serial.println("> Sending response...");

                            client.println(stats.getStatString());
                        }

                        // Parse GET /<index>
                        else if (header.startsWith("GET /"))
                        {
                            int index = header.substring(5).toInt();

                            if (index < 0 || index >= stats.getStatLength())
                            {
                                Serial.println("> Invalid index");
                                client.println("Invalid index");
                                return;
                            }

                            char stat = stats.getStat(index);

                            Serial.print("> Stat: ");
                            Serial.println(stat);
                            Serial.println("> Sending response...");

                            client.println(stat);
                        }

                        // Parse POST /<index>/<value>
                        else if (header.startsWith("POST /"))
                        {
                            int index = header.substring(6, header.indexOf('/', 6)).toInt();
                            char value = header.substring(header.indexOf('/', 6) + 1).charAt(0);

                            if (index < 0 || index >= stats.getStatLength())
                            {
                                Serial.println("> Invalid index");
                                client.println("Invalid index");
                                return;
                            }

                            stats.setStat(index, value);

                            Serial.print("> Changed stat '");
                            Serial.print(index);
                            Serial.print("' to '");
                            Serial.print(value);
                            Serial.println("'");

                            Serial.println("> Sending response...");

                            client.println("OK");
                        }
                    }
                    else
                    {
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {
                    currentLine += c;
                }
            }
        }

        Serial.println("Client disconnected");
        client.stop();
    }

    // Update car from stats
    if (stats.getStat(0) == 'D')
    {
        car.stop();
    }
    else if (stats.getStat(0) == 'M')
    {
        car.manual_frontleft(Stats::speedTodirectionSpeed(stats.getStat(1), Stats::charToSpeed(stats.getStat(2))));
        car.manual_frontright(Stats::speedTodirectionSpeed(stats.getStat(3), Stats::charToSpeed(stats.getStat(4))));
        car.manual_rearleft(Stats::speedTodirectionSpeed(stats.getStat(5), Stats::charToSpeed(stats.getStat(6))));
        car.manual_rearright(Stats::speedTodirectionSpeed(stats.getStat(7), Stats::charToSpeed(stats.getStat(8))));
    }
    else if (stats.getStat(0) == 'A')
    {
        const float angle = Stats::charToAngle(stats.getStat(9));
        const float speed = Stats::speedTodirectionSpeed(stats.getStat(10), Stats::charToSpeed(stats.getStat(11)));

        if (angle < 0)
        {
            car.left(speed);
        }
        else if (angle > 0)
        {
            car.right(speed);
        }
        else
        {
            car.drive(speed);
        }
    }
    else if (stats.getStat(0) == 'T')
    {
        car.drive(0.3);
    }
    else
    {
        Serial.println("Invalid status");
    }
}