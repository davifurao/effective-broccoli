import paho.mqtt.client as mqtt
import time
import random

#Publisher
client = mqtt.Client()
client.connect("127.0.0.1", 1883, 60)
client.loop_start()
client.publish("topic/test", random.randint(0,30))
time.sleep(2)  # import time
try:
    while True:
        pass
except KeyboardInterrupt:
    print("\nSaindo")
    client.disconnect()
    client.loop_stop()
