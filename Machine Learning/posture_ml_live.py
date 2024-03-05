import pyrebase
import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from threading import Timer
import time
from datetime import datetime

# Firebase configuration
firebase_config = {
    "apiKey": "xxxxxxxxxxxxxxxxxxxx",
    "authDomain": "xxxxxxxxxxxxxxxxxxxx",
    "databaseURL": "xxxxxxxxxxxxxxxxxxxx",
    "storageBucket": "xxxxxxxxxxxxxxxxxxxx"
}

# Initialize Firebase
firebase = pyrebase.initialize_app(firebase_config)
db = firebase.database()

def fetch_data():
    sensor_data = db.child("sensor_data").get()
    data = [sensor.val() for sensor in sensor_data.each()] if sensor_data.each() else []
    return pd.DataFrame(data)

def train_model():
    df = fetch_data()
    if not df.empty:
        X = df[['distance', 'pressure']]
        y = df['label']
        model = RandomForestClassifier()
        model.fit(X, y)
        print("Model retrained.")
        return model
    else:
        print("No data available for retraining.")
        return None

def retrain_model(interval=3600):
    global rf_model
    rf_model = train_model()
    Timer(interval, retrain_model).start()

last_predicted = None

def monitor_new_data():
    global last_predicted
    while True:
        time.sleep(3)  # Check for new data every 3 seconds
        new_data = fetch_data()
        if not new_data.empty:
            last_entry = new_data.iloc[-1]
            if last_predicted != last_entry.to_dict():
                predict_posture(last_entry)
                last_predicted = last_entry.to_dict()

def predict_posture(data):
    if rf_model:
        # Generate a current timestamp in a sortable format (ISO 8601)
        current_timestamp = datetime.now().isoformat()

        # Ensure input data for prediction is in the same format as the training data
        input_data = pd.DataFrame([[data['distance'], data['pressure']]], columns=['distance', 'pressure'])
        prediction = rf_model.predict(input_data)

        # Define a fixed key for the prediction entry
        prediction_key = "current_prediction"

        # Construct the new prediction data
        new_prediction_data = {
            "timestamp": current_timestamp,
            "prediction": int(prediction[0])
        }

        # Update the single entry in the database with the new prediction
        db.child("predictions").child(prediction_key).set(new_prediction_data)
        print(f"Prediction updated: {new_prediction_data}")
    else:
        print("Model not available for predictions.")

# Start the retraining and monitoring processes
rf_model = None
retrain_model(interval=3600)
monitor_new_data()