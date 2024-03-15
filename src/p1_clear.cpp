#include "../include/software_training/p1_clear.hpp"
using namespace std::literals::chrono_literals;

namespace composition {

p1_clear::p1_clear(const rclcpp::NodeOptions &options) 
    : Node("p1_clear", options){
    // complete this code
    turtle_names = {"turtlesim"};

    // create a client to the /kill service
    client = this->create_client<turtlesim::srv::Kill>("/kill");
    
    p1_clear::kill();
}

void p1_clear::kill() {
    // complete this code
      // check if service exists
        // if (!client->wait_for_service(2s)) {
        //     if (!rclcpp::ok()) {
        //     RCLCPP_ERROR(this->get_logger(),
        //                 "Interrupted while waiting for service. Exiting!");
        //     return;
        //     }
        //     RCLCPP_INFO(this->get_logger(), "Service not available after waiting");
        //     return;
        // }
        // RCLCPP_INFO(this->get_logger(), "TURTLES KILLED.");

    // iterate through all the turtles
    for (auto name : turtle_names) {
        // create a request message
        auto request = std::make_shared<turtlesim::srv::Kill::Request>();
        // set the name field of the message
        request->name = name;
        // create a callback (kind of difficult so you can copy paste)
        auto callback = [this](rclcpp::Client<turtlesim::srv::Kill>::SharedFuture response) -> void {
                (void)response; // void the response since we don't need one
                RCLCPP_INFO(this->get_logger(), "Turtle  Killed");
                rclcpp::shutdown(); // kill this node
        };
        // send an asynchronous request with the request message and the callback as parameters
        auto result = client->async_send_request(request, callback);

    }
}

#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(composition::p1_clear)

} // namespace composition