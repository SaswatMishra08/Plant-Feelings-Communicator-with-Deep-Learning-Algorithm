#from ultralytics import YOLO
# #from ultralytics.yolo.v8.detect.predict import Detection
# import cv2

# model= YOLO("C:\Users\mysel\Downloads\yolov8m.pt")
# model.predict(source="0",show=True, conf=0.5)

from ultralytics import YOLO
import cv2
import serial

# Define the path to the YOLOv5 model file
model_path = "C:/Users/mysel/Downloads/yolov8m.pt"

# Load the YOLOv5 model
model = YOLO(model_path)

# Define the source for prediction (0 for webcam, or specify an image path)
source = "0"  # Use "0" for webcam

# Set up serial communication with Arduino
arduino = serial.Serial('COM3', 9600)  # Replace 'COM3' with your Arduino serial port

# Perform object detection using YOLOv5
results = model(source=source,  show=True, conf=0.5)
print("yes")

# Check if weeds' class is detected
weeds=["Carpetweeds", "Cotton""Crabgrass", "Eclipta", "Goosegrass", "Morningglory", "Nutsedge", "PalmerAmaranth", "Prickly-Sida", "Purslane", "Ragweed", "Sicklepod", "SpottedSpurge", "SpurredAnoda", "Swinecress", "Waterhemp"]
for pred in results:
    if pred.names[0] in weeds:
        # Send message to Arduino to turn on LED

        arduino.write(b'1')  # Send '1' to Arduino

    else:
        # Send message to Arduino to turn off LED
        
        arduino.write(b'0')  # Send '0' to Arduino

# Display the results
results.show()
print("yyyyyes")
# Save the results
results.save()

# Convert the results to OpenCV format for additional processing
image = results.render()[:, :, ::-1]  # Convert RGB image to BGR for OpenCV

# Display the image using OpenCV
cv2.imshow("YOLOv5 Object Detection", image)
cv2.waitKey(0)
cv2.destroyAllWindows()

# Close serial connection
arduino.close()

