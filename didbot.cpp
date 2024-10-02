#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <ctime>
#include <fstream>
#include <random>

// Function to convert a string to lowercase for comparison
void toLowerCase(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

// Function to return a greeting based on the time of day
std::string getGreeting() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    if (ltm->tm_hour < 12) return "Good morning";
    else if (ltm->tm_hour < 18) return "Good afternoon";
    else return "Good evening";
}

// A class to manage user profile and chat history
class UserProfile {
private:
    std::string userName;
    std::string mood;
    std::vector<std::string> conversationHistory;

public:
    UserProfile() : mood("neutral") {}

    void setUserName(const std::string& name) {
        userName = name;
    }

    std::string getUserName() const {
        return userName;
    }

    void setMood(const std::string& newMood) {
        mood = newMood;
    }

    std::string getMood() const {
        return mood;
    }

    void addToHistory(const std::string& message) {
        conversationHistory.push_back(message);
    }

    void showHistory() const {
        std::cout << "Conversation History:\n";
        for (const auto& msg : conversationHistory) {
            std::cout << msg << "\n";
        }
    }

    // Log conversation to a file
    void logToFile() const {
        std::ofstream file("conversation_log.txt", std::ios::app);
        if (file.is_open()) {
            for (const auto& msg : conversationHistory) {
                file << msg << "\n";
            }
            file.close();
        }
    }
};

// A map of keywords to responses
std::map<std::string, std::string> responseMap = {
    {"success", "Success is not just a destination, it's the grind, baby. Keep pushing forward!"},
    {"hustle", "The hustle never stops. We grind, we rise. That's how we do!"},
    {"music", "Music is the vibe, it’s how we tell our story to the world."},
    {"inspire", "Always be inspiring, always be motivated. Greatness is in your hands."},
    {"money", "Money comes and goes, but your legacy stays. Focus on greatness."},
    {"life", "Life's a marathon, not a sprint. Stay patient and consistent."},
    {"dream", "Dream big and never let anyone tell you otherwise. Greatness awaits!"},
    {"motivate", "Let me motivate you: You got the power, the will, and the skill to make it happen!"},
    {"grind", "It’s all about the grind, day in and day out."},
    {"vision", "Your vision has to be clear. Keep it focused, keep it sharp."},
    {"hard work", "Hard work beats talent when talent doesn't work hard."},
    {"legacy", "Build a legacy, not just a career. That’s what truly matters."},
    {"perseverance", "Perseverance is what separates winners from the rest."},
    {"happiness", "Happiness comes from within, from doing what you love."},
    {"fear", "Fear is temporary, but regret lasts forever. Face your fears."},
    {"confidence", "Confidence isn’t just about what you say, it’s about what you do."},
    {"growth", "Growth happens when you push past your limits."},
    {"team", "A strong team makes the dream work. Surround yourself with greatness."},
    {"sacrifice", "You gotta sacrifice something to gain everything you want."},
    {"ambition", "Your ambition should scare you; that’s when you know it’s right."},
    {"faith", "Faith keeps you going when the road gets rough. Trust the process."},
    {"change", "You can’t be afraid of change, embrace it and evolve."},
    {"leadership", "A true leader doesn’t create followers; they create more leaders."},
    {"passion", "Passion is what turns dreams into reality. Find yours and chase it."},
    {"challenge", "Challenges are stepping stones to your success."},
    {"failure", "Failure is a lesson, not a loss. Learn from it and keep moving."},
    {"love", "Love what you do, and the world will love you back."},
    {"respect", "Respect is earned, not given. Work for it every day."},
    {"focus", "Stay focused on your goals, not distractions."},
    {"energy", "Bring energy to everything you do. That's how you win."},
    {"belief", "Believe in yourself even when nobody else does."},
    {"visionary", "Be a visionary. See the world not for what it is, but for what it could be."},
    {"opportunity", "Opportunities don’t come to those who wait, they come to those who hustle."},
    {"impact", "Make an impact, don’t just make an impression."},
    {"trust", "Trust the journey, even when you don’t understand the path."},
    {"ambition", "Ambition fuels greatness. Keep striving for more."},
    {"mindset", "Your mindset will determine your altitude. Think big."},
    {"risk", "No risk, no reward. Step out of your comfort zone."},
    {"persistence", "Persistence breaks down resistance."},
    {"discipline", "Discipline is the bridge between goals and accomplishment."},
    {"purpose", "Find your purpose, and everything else will fall into place."},
    {"power", "Power isn’t given, it’s taken through hard work and dedication."},
    {"determination", "Determination is the fuel that keeps the fire burning."},
    {"setbacks", "Setbacks are setups for comebacks."},
    {"chase", "Chase your dreams with everything you got."},
    {"ownership", "Own your success, own your failures. That’s how you grow."},
    {"patience", "Success takes time. Be patient, but relentless."},
    {"drive", "Keep that drive alive, even when no one else believes in you."},
    {"ambition", "Ambition without action is just a dream. Make it happen."},
    {"goal", "Set a goal so big it scares you, then go achieve it."},
    {"challenges", "Challenges make you stronger, don’t run from them."},
    {"adversity", "Adversity introduces a person to themselves. Face it head-on."},
    {"greatness", "Greatness is a habit, not an act. Make it part of your daily grind."},
    {"self-belief", "Believe in yourself when no one else does."},
    {"fearless", "You have to be fearless in the pursuit of what sets your soul on fire."},
    {"timing", "Timing is everything. Trust the process."},
    {"grit", "Grit is the difference between average and extraordinary."},
    {"doubt", "Doubt kills more dreams than failure ever will. Keep going."},
    {"determination", "Determination is doing whatever it takes, no matter how long it takes."},
    {"ownership", "Own every decision, every move you make. That’s power."},
    {"overcome", "Overcome every obstacle with confidence and grace."},
    {"vision", "Keep your vision sharp, and your grind sharper."},
    {"resilience", "Resilience is the key to survival in the game of life."},
    {"authentic", "Be authentic. The world doesn’t need copies; it needs originals."},
    {"clarity", "Clarity comes when you quiet the noise and focus on what matters."},
    {"humility", "Stay humble, stay hungry."},
    {"tenacity", "Tenacity is what separates the weak from the strong."},
    {"faith", "Faith is seeing light with your heart when all your eyes see is darkness."},
    {"empower", "Empower yourself so you can empower others."},
    {"focus", "Laser focus on your goals, and everything else will fall in place."},
    {"potential", "Unlock your potential by pushing past your limits."},
    {"strength", "Strength isn’t physical; it’s mental. Keep your mind strong."},
    {"balance", "Balance ambition with gratitude. That’s how you find peace."},
    {"integrity", "Your integrity will take you farther than anything else."},
    {"ambition", "Let your ambition guide your actions, not your emotions."},
    {"legacy", "Your legacy is what people will remember. Make it impactful."},
    {"vision", "Hold onto your vision when no one else sees it."},
    {"progress", "Progress, not perfection. Keep moving forward."},
    {"clarity", "Find clarity in chaos, and you’ll find success."},
    {"accountability", "Hold yourself accountable before anyone else does."},
    {"wealth", "True wealth is in your knowledge, your grind, your character."},
    {"motivation", "Motivation gets you started; discipline keeps you going."},
    {"effort", "Success isn’t guaranteed, but your effort is. Give it 100%."},
    {"authenticity", "Authenticity will attract the right people to you."},
    {"truth", "Speak your truth, and the world will respond to it."},
    {"grind", "Grind in silence, let your success make the noise."},
    {"focus", "Focus on the outcome, not the obstacles."},
    {"ambition", "Ambition drives the dream, but discipline makes it real."},
    {"visionary", "Be a visionary—see what others can’t, and work until they can."}
};


// Function to generate chatbot responses based on mood and input
std::string pDiddyBotResponse(const std::string& input, const std::string& mood) {
    // Specific responses for common phrases
    if (input.find("how are you") != std::string::npos) {
        return "Diddy: I'm just a code on a screen, but I'm here for you!";
    }
    if (input.find("cheers") != std::string::npos) {
        return "Diddy: Cheers! Let's keep the positive vibes rolling!";
    }
    if (input.find("tough") != std::string::npos || input.find("life's been tough") != std::string::npos) {
        return "Diddy: It's okay to feel tough times. Just remember, you have the strength to rise above.";
    }

    // Default keyword response logic
    for (const auto& [keyword, response] : responseMap) {
        if (input.find(keyword) != std::string::npos) {
            return "Diddy: " + response;
        }
    }

    // Default responses based on mood
    if (mood == "happy") {
        return "Diddy: You sound happy! Let's keep this positive energy going!";
    } else if (mood == "sad") {
        return "Diddy: It's okay to be down sometimes, but don't forget—greatness is within you.";
    } else {
        return "Diddy: You got this, keep it real and stay focused! Elaborate a bit more to give me some context man?";
    }
}

// Function to detect mood based on user input
std::string detectMood(const std::string& input) {
    if (input.find("happy") != std::string::npos || input.find("excited") != std::string::npos) {
        return "happy";
    } else if (input.find("sad") != std::string::npos || input.find("down") != std::string::npos) {
        return "sad";
    } else {
        return "neutral";
    }
}

// Main chatbot program
int main() {
    UserProfile user;
    std::string userInput;

    // Introduction and user profiling
    std::cout << getGreeting() << ", welcome to P. Diddy Bot! What's your name?\n";
    std::getline(std::cin, userInput);
    user.setUserName(userInput);
    std::cout << "Nice to meet you, " << user.getUserName() << "! What's on your mind today?\n";

    // Main chatbot loop
    while (true) {
        std::getline(std::cin, userInput);
        std::string lowerInput = userInput;
        toLowerCase(lowerInput);

        // Exit command
        if (lowerInput == "exit") {
            user.logToFile();  // Log the conversation before exiting
            std::cout << "Diddy: Stay on your grind, we out!\n";
            break;
        }

        // Help command
        if (lowerInput == "help") {
            std::cout << "Diddy: You can ask me anything or just talk about your day! Type 'exit' to end the conversation.\n";
            continue;
        }

        // Detect mood and respond
        std::string mood = detectMood(lowerInput);
        std::string response = pDiddyBotResponse(lowerInput, mood);
        user.addToHistory("User: " + userInput);
        user.addToHistory(response);
        std::cout << response << "\n";
    }

    return 0;
}
