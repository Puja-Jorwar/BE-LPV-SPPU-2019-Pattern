import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# Load Dataset
data = pd.read_csv(
    "/content/housing.csv",
    delim_whitespace=True,
    header=None
)

# Column Names
data.columns = [
    "CRIM", "ZN", "INDUS", "CHAS", "NOX",
    "RM", "AGE", "DIS", "RAD", "TAX",
    "PTRATIO", "B", "LSTAT", "MEDV"
]

# Features and Target
X = data.drop("MEDV", axis=1)
y = data["MEDV"]

# Split Dataset
X_train, X_test, y_train, y_test = train_test_split(
    X, y,
    test_size=0.2,
    random_state=42
)

# Feature Scaling
scaler = StandardScaler()

X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Build Deep Neural Network
model = Sequential()

model.add(Dense(64, activation='relu',
                input_shape=(X_train.shape[1],)))

model.add(Dense(32, activation='relu'))

model.add(Dense(16, activation='relu'))

# Output Layer for Regression
model.add(Dense(1))

# Compile Model
model.compile(
    optimizer='adam',
    loss='mse',
    metrics=['mae']
)

# Train Model
model.fit(
    X_train,
    y_train,
    epochs=100,
    batch_size=16,
    validation_split=0.1
)

# Evaluate Model
loss, mae = model.evaluate(X_test, y_test)

print("\nMean Absolute Error:", mae)

# Predictions
predictions = model.predict(X_test)

print("\nSample Predictions:")
print(predictions[:5])



