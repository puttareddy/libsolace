
#include <solace/char.hpp>
#include <solace/io/serial.hpp>
#include <solace/stringBuilder.hpp>


#include <iostream>

using Solace::uint32;

void enumeratePorts() {
	for (const auto& descriptor : Solace::IO::Serial::enumeratePorts()) {
		printf("%s:\n\t-%s\n\t-(%s)\n",
			descriptor.file.toString().c_str(),
			descriptor.description.toString().c_str(),
            descriptor.hardwareId.toString().c_str()
			);
	}
}


int main(int argc, char **argv) {

	if (argc == 1) { // No-arg call: list ports and exit
		enumeratePorts();
		return 0; 
	}

    const uint32 boudRate = (argc > 2)
        ? atoi(argv[2])
        : 115200;

	const uint32 bufferSize = (argc > 3) 
		? atoi(argv[3])
        : 120;

	const auto file = Solace::Path::parse(argv[1]);
    printf("Opening port: '%s', boudrate: %d\n", file.toString().c_str(), boudRate);

	Solace::IO::Serial serial(file, boudRate);
    Solace::ByteBuffer readBuffer(bufferSize);
    Solace::ByteBuffer formatBuffer(bufferSize);

    const Solace::StringBuilder sb(formatBuffer);

    while (true) {
        const auto bytesRead = serial.read(readBuffer);

        if (bytesRead < 0) {
            break;
        } else if (bytesRead == 0) {
            if (!serial.waitReadable(10000)) {
                printf("Wait failed!\n");
                break;
            }
        } else {
            std::cout.write((const char*)readBuffer.data(), readBuffer.position());
            std::cout.flush();

            readBuffer.rewind();
        }

//        if (!readBuffer.hasRemaining()) {
//            for (Solace::WriteBuffer::size_type i = 0; i < readBuffer.position(); ++i) {
//                const auto c = readBuffer.get(i);

//                if (Solace::Char::isPrintable(c)) {
//                    formatBuffer << c;
//                } else if (c == '\r') {
//                    formatBuffer << c;
//                    std::cout.write((const char*)formatBuffer.data(), formatBuffer.position());
//                    std::cout.flush();
//                    formatBuffer.rewind();
//                }

//                if (!formatBuffer.hasRemaining()) {
//                    std::cout.write((const char*)formatBuffer.data(), formatBuffer.position());
//                    std::cout.flush();
//                    formatBuffer.rewind();
//                }
//            }
//            readBuffer.rewind();
//        }
    }
}