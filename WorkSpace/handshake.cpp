#include <dji_vehicle.hpp>
#include <iostream>

// Use the DJI OSDK namespace
using namespace DJI::OSDK;

int main()
{
    // --- Setup ---
    // You MUST change these values to match your setup
    std::string serial_port = "/dev/ttyUSB0"; // Example for Linux
    uint32_t baud_rate = 230400;             // Common baud rate

    // 2. Instantiate Vehicle
    // We pass 'false' to indicate we are not using advanced serial features
    Vehicle* vehicle = new Vehicle(serial_port, baud_rate, false);

    // Check if the Vehicle object was created
    if (vehicle == nullptr)
    {
        std::cout << "Error: Failed to create Vehicle object." << std::endl;
        return -1;
    }

    // 3. Prepare Activation Data
    // !! REPLACE WITH YOUR OWN APP ID AND KEY !!
    int my_app_id = 1234567; // Your App ID
    std::string my_app_key = "YOUR_APP_KEY_GOES_HERE"; 

    Vehicle::ActivateData activation_data;
    activation_data.ID = my_app_id;
    activation_data.encKey = my_app_key.c_str();

    std::cout << "Attempting to activate (handshake) with drone..." << std::endl;

    // 4. Call activate() and store the result
    ACK::ErrorCode ack = vehicle->activate(&activation_data);

    // 5. Check the Result (This is the core of the task)
    if (ACK::getError(ack))
    {
        // Handshake FAILED
        std::cout << "Activation Failed. Error: " 
                  << ACK::getErrorCodeMessage(ack) << std::endl;
        
        // This is where you would trigger the "cancel takeoff" logic
        // for your user story.
        delete vehicle;
        return -1; 
    }
    else
    {
        // Handshake SUCCESS
        std::cout << "Activation Success." << std::endl;
        
        // Now the SDK is initialized and connected.
        // We can proceed to the next checks (GPS, Battery).
    }

    // ... Your other code (like checkGPS(), checkBattery()) would go here ...

    // Cleanup
    delete vehicle;
    return 0;
}