CREATE DATABASE IF NOT EXISTS cooperative;
USE cooperative;
 
CREATE TABLE IF NOT EXISTS ProduceDeliveries (
    FarmerNumber   INT PRIMARY KEY,
    FarmerName     VARCHAR(50),
    ProduceType    VARCHAR(20),
    Quantity       INT,
    PricePerUnit   DECIMAL(10,2),
    PaymentStatus  VARCHAR(10)
);
 
INSERT INTO ProduceDeliveries VALUES
    (101, 'Mwangi Kamau',   'Milk',       120, 55,  'Pending'),
    (102, 'Wanjiku Njeri',  'Coffee',     85,  120, 'Paid'),
    (103, 'Peter Maina',    'Potatoes',   300, 40,  'Pending'),
    (104, 'Akinyi Otieno',  'Maize',      250, 65,  'Pending'),
    (105, 'Mutiso Musyoka', 'Milk',       150, 55,  'Paid'),
    (106, 'Chebet Kiptoo',  'Vegetables', 95,  80,  'Pending');
