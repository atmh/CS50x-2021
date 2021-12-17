-- Keep a log of any SQL queries you execute as you solve the mystery.

.tables

.schema TABLE_NAME

.schema crime_scene_reports

SELECT * from crime_scene_reports;

SELECT * from crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street"; -- 10.15am

SELECT * from interviews WHERE year = 2020 AND month = 7 AND day = 28; -- left within 10 minutes, talked to someone less than a minute, , withdraw on fifer street, earliest flight on 29th

SELECT license_plate from courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute < 25; -- license plate

SELECT name FROM people
WHERE license_plate IN (SELECT license_plate from courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute < 25) -- license plate
AND phone_number IN (SELECT caller from phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60)
AND id IN (
    SELECT person_id FROM bank_accounts
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28
    AND transaction_type = "withdraw"
    AND atm_transactions.atm_location = "Fifer Street"
) -- withdraw
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute ASC LIMIT 1)) -- flight
;
-- Ernest


SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute ASC LIMIT 1); -- earliest flight on 29th
-- London


SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND caller = (SELECT phone_number FROM people WHERE name = "Ernest") AND duration < 60); -- call < 1 minute from Ernest
-- Berthold