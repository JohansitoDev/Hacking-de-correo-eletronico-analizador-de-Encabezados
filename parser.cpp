#include <iostream>
#include <fstream>
#include <string>
#include <map>

class EmailParser {
public:
  
    EmailParser(const std::string& filename) : filename_(filename) {}

    bool parse() {
        std::ifstream file(filename_);
        if (!file.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo " << filename_ << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line) && !line.empty() && line != "\r") {
            size_t colon_pos = line.find(':');
            if (colon_pos != std::string::npos) {
                
                std::string header_name = line.substr(0, colon_pos);
                std::string header_value = line.substr(colon_pos + 2);
                
                
                headers_[header_name] = header_value;
            }
        }
        file.close();
        return true;
    }

    void printHeaders() const {
        std::cout << "--- Encabezados del Correo ---" << std::endl;
        for (const auto& pair : headers_) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    
    std::string getHeader(const std::string& header_name) const {
        auto it = headers_.find(header_name);
        if (it != headers_.end()) {
            return it->second;
        }
        return ""; 
    }

private:
    std::string filename_;
    std::map<std::string, std::string> headers_;
};

int main() {

    std::string email_file_name = "email.txt";
    
    
    EmailParser parser(email_file_name);
    if (parser.parse()) {
        parser.printHeaders();

    
        std::cout << "\n--- Acceso directo a un encabezado ---" << std::endl;
        std::string from = parser.getHeader("From");
        if (!from.empty()) {
            std::cout << "Remitente: " << from << std::endl;
        }
        
        std::string subject = parser.getHeader("Subject");
        if (!subject.empty()) {
            std::cout << "Asunto: " << subject << std::endl;
        }
    }

    return 0;
}
