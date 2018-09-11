using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.IO;
using System.Linq;

namespace Server
{
    class Server
    {
        private static int WriteStringToFile(string buff, string ipAddress)
        {
            Console.WriteLine("WriteStringToFile - got the string:{0} from client IP address:{1}", buff, ipAddress);
            String timeStamp = "_" + DateTime.Now.ToString("yyyyMMddHHmmssffff") + ".txt";
            string fileName = ipAddress.Replace('.', '_') + timeStamp;
            var path = Path.Combine(Directory.GetCurrentDirectory(), fileName);
            Console.WriteLine("WriteStringToFile - the full path for the file to be created is:{0}", path);

            // This text is added only once to the file.
            if (File.Exists(path) == false)
            {
                // Create a file to write to.
                Console.WriteLine("WriteStringToFile - file in path:{0} was created", path);
                string createText = buff + Environment.NewLine;
                File.WriteAllText(path, createText);
            }
            else
            {
                Console.WriteLine("WriteStringToFile - file in path:{0} already exist", path);
                return 0;
            }

            return buff.Length;
        }

        private static string GetStreamAsEncodedString(byte[] buffer)
        {
            string dataReceived;
            if (buffer.Length < 2)
            {
                Console.WriteLine("GetStreamAsEncodedString - buffer is too short...");
                return String.Empty;
            }

            // convert the data received into a string according to the specified
            // encoding that the client used which is indicated as follows:
            // buffer[0] == 1 --> UNICODE
            // buffer[0] == 0 --> ASCII
            if (buffer[0] == 1)
            {
                Console.WriteLine("GetStreamAsEncodedString - got the buffer in UNICODE");
                buffer = buffer.Skip(1).ToArray();
                dataReceived = Encoding.Default.GetString(buffer, 0, buffer.Length);
                return dataReceived;
            }

            else if (buffer[0] == 0)
            {
                Console.WriteLine("main - got the buffer in ASCII");
                dataReceived = Encoding.ASCII.GetString(buffer, 1, buffer.Length - 1);
                return dataReceived;
            }

            else
            {
                Console.WriteLine("GetStreamAsEncodedString - first byte of the stream buffer was not valid (not 0 nor 1)");
                return String.Empty;
            }
        }

        static void Main(string[] args)
        {
            // ------- unit test -------
            /*
            bool res = invokeUnitTests();
            if (res == false)
            {
                Console.WriteLine("Main - invokeUnitTests FAILED");
            }
            */
            // ------- unit test -------

            // get the port number and ip address
            if (args.Length < 2)
            {
                Console.WriteLine("main - not enough arguments provided,excpeting two arguments: ip_address port_number, aborting...");
                return;
            }

            string serverIp = args[0];
            int serverPortNum = Int32.Parse(args[1]);
            Console.WriteLine("main - got ip address:{0}, and port number:{1}", serverIp, serverPortNum);

            // listen at the specified IP and port no.
            IPAddress localAdd = IPAddress.Parse(args[0]);
            TcpListener listener = new TcpListener(localAdd, serverPortNum);
            TcpClient client = null;
            Console.WriteLine("main - server is listening on ip:{0}, port:{1}...", serverIp, serverPortNum);
            listener.Start();
            try
            {
                while (true)
                {
                    // incoming client connected
                    client = listener.AcceptTcpClient();
                    string clientIpAddress = ((IPEndPoint)client.Client.RemoteEndPoint).Address.ToString();

                    // get the incoming data through a network stream
                    NetworkStream nwStream = client.GetStream();
                    byte[] buffer = new byte[client.ReceiveBufferSize];
                    Console.WriteLine("main - client.ReceiveBufferSize is:{0}", client.ReceiveBufferSize);

                    // read incoming stream
                    int bytesRead = nwStream.Read(buffer, 0, client.ReceiveBufferSize);
                    Console.WriteLine("main - read {0} bytes from buffer", bytesRead);
                    string dataReceived = GetStreamAsEncodedString(buffer);
                    if (String.IsNullOrEmpty(dataReceived) == true)
                    {
                        throw new Exception("main - had issues with the recived buffer");
                    }

                    int writtenBytes = WriteStringToFile(dataReceived, clientIpAddress);
                    if (writtenBytes == dataReceived.Length)
                    {
                        Console.WriteLine("main - successfully wrote {0} bytes to file", writtenBytes);
                    }
                    else
                    {
                        throw new Exception("main - DID NOT write all bytes to file successfully");
                    }

                    // close the client socket connection
                    client.Close();
                }
            }

            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                Console.WriteLine("main - caught an excpetion, aborting...");
                if (client != null)
                {
                    client.Close();
                }
            }

            listener.Stop();
            Console.WriteLine("main - terminating...");
        }

        // ---- unit tests -----
        /*
        private static bool invokeUnitTests()
        {
            bool res = convertBigToLittleTests();
            if (res == false)
            {
                Console.WriteLine("unit tests::invokeUnitTests - convertBigToLittleTests FAILED");
                return false;
            }
            return res;
        }

        private static bool convertBigToLittleTests()
        {
            char[] utf16Buff3 = { 'a', '\0', 'b', '\0', '\0', '\0', 'd', '\0', 'R', '\0', 'U', '\0', 'Y', '\0', 'q', '\0', 'o', '\0' };
            char[] utf16Buff3Swapped = { '\0', 'a', '\0', 'b', '\0', '\0', '\0', 'd', '\0', 'R', '\0', 'U', '\0', 'Y', '\0', 'q', '\0', 'o' };
            bool res = ConvertBigToLittleEndian(utf16Buff3);
            if (res == false)
            {
                Console.WriteLine("unit tests::convertBigToLittle - ConvertBigToLittleEndian was not successfull");
                return false;
            }

            for (int i = 0; i < utf16Buff3.Length; ++i)
            {
                if (utf16Buff3[i] != utf16Buff3Swapped[i])
                {
                    return false;
                }
            }

            return true;
        }
        */
        // ---- unit tests -----
    }
}