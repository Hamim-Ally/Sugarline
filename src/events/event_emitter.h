#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <stdexcept>
#include <type_traits>

class EventEmitter {
public:
    // Add listener
    template<typename... Args>
    void on(const std::string& event, std::function<void(Args...)> cb) {
        Channel<Args...>* ch;

        if (!channels.count(event)) {
            ch = new Channel<Args...>();
            channels[event].reset(ch);
        } else {
            ch = dynamic_cast<Channel<Args...>*>(channels[event].get());
            if (!ch) throw std::runtime_error("Signature mismatch for event: " + event);
        }

        ch->listeners.push_back(cb);
    }

    // Remove listener (simple version clears all for that event)
    void off(const std::string& event) {
        channels.erase(event);
    }

protected:
    // Emit event with no arguments (non-template version)
    void emit(const std::string& event) {
        if (!channels.count(event)) return;
        
        // For empty args, we need Channel<> which is Channel with empty parameter pack
        typedef Channel<> NoArgChannel;
        auto* ch = dynamic_cast<NoArgChannel*>(channels[event].get());
        if (!ch) return;  // No matching listeners

        for (auto& cb : ch->listeners) cb();
    }

    // Emit event with arguments (only matches when Args... is not empty)
    template<typename T, typename... Args>
    void emit(const std::string& event, T first, Args... rest) {
        if (!channels.count(event)) return;

        auto* ch = dynamic_cast<Channel<T, Args...>*>(channels[event].get());
        if (!ch) return;  // No matching listeners

        for (auto& cb : ch->listeners) cb(first, rest...);
    }

private:
    struct IChannel {
        virtual ~IChannel() = default;
    };

    template<typename... Args>
    struct Channel : IChannel {
        std::vector<std::function<void(Args...)>> listeners;
    };

    std::unordered_map<std::string, std::unique_ptr<IChannel>> channels;
};
