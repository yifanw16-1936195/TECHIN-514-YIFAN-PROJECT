import pyrebase
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score
from sklearn.ensemble import RandomForestClassifier
from sklearn.neural_network import MLPClassifier

# Step 1: Fetch the Data from Firebase

firebase_config = {
    "apiKey": "AIzaSyBv3VISnijb9p1HwbtUMjp8YBggXMDjT9I",
    "authDomain": "techin514-final-default-rtdb.firebaseio.com",
    "databaseURL": "https://techin514-final-default-rtdb.firebaseio.com/",
    "storageBucket": "techin514-final-default-rtdb.appspot.com"
}

firebase = pyrebase.initialize_app(firebase_config)
db = firebase.database()
sensor_data = db.child("sensor_data").get()

data = []
for sensor in sensor_data.each():
    data.append(sensor.val())

df = pd.DataFrame(data)

# Step 2: Prepare the Dataset for Machine Learning

X = df[['distance', 'pressure']]  # Features
y = df['label']  # Target variable

# Split dataset into training set and test set
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=35)  # 80% training and 20% testing


# Step 3: Train Classification Models

# Train SVM
svm_model = SVC()
svm_model.fit(X_train, y_train)
# Predictions
svm_predictions = svm_model.predict(X_test)

# Train Random Forest
rf_model = RandomForestClassifier()
rf_model.fit(X_train, y_train)
# Predictions
rf_predictions = rf_model.predict(X_test)

# Train Neural Network
nn_model = MLPClassifier(hidden_layer_sizes=(10, 10), max_iter=5000)
nn_model.fit(X_train, y_train)
# Predictions
nn_predictions = nn_model.predict(X_test)

# Step 4: Evaluate the Models

# Collect accuracies
accuracies = {
    "SVM": accuracy_score(y_test, svm_predictions),
    "Random Forest": accuracy_score(y_test, rf_predictions),
    "Neural Network": accuracy_score(y_test, nn_predictions)
}

# Print accuracies
for model_name, accuracy in accuracies.items():
    print(f"{model_name} Accuracy: {accuracy}")

# Determine the model with the highest accuracy
best_model_name = max(accuracies, key=accuracies.get)
best_accuracy = accuracies[best_model_name]

print(f"\nModel with the highest accuracy: {best_model_name} ({best_accuracy})")


# Step 5: Console Input for Predictions - FOR TESTING PURPOSES

# def make_prediction(model, distance, pressure):
#     prediction = model.predict([[distance, pressure]])
#     labels = {1: "good posture", 2: "leaning forward", 3: "leaning backward", 4: "sitting at front", 5: "sitting at back"}
#     return labels[prediction[0]]

# distance_input = float(input("Enter distance: "))
# pressure_input = float(input("Enter pressure: "))

# print("SVM Prediction:", make_prediction(svm_model, distance_input, pressure_input))
# print("Random Forest Prediction:", make_prediction(rf_model, distance_input, pressure_input))
# print("Neural Network Prediction:", make_prediction(nn_model, distance_input, pressure_input))