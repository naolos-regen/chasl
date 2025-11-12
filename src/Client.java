import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Client
{
        public static void main (String ... args)
        {
                final String SERVER_ADDR = "127.0.0.1";
                final int SERVER_PORT = 8080;

                try 
                (
                final Socket socket = new Socket(SERVER_ADDR, SERVER_PORT);
                final Scanner scanner = new Scanner(System.in);
                final PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                final BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))
                )
                {
                        System.out.println("Connected to Server");

                        while (true)
                        {
                                System.out.print("Enter Message: ");

                                final String userInput = scanner.nextLine();

                                if ("exit".equalsIgnoreCase(userInput))
                                        break;

                                out.println(userInput);

                                final String serverResponse = in.readLine();
                                System.out.println("Server Echoed: " + serverResponse);
                        }
                }
                catch (UnknownHostException e)
                {
                        System.err.println("Server not found: " + e.getMessage());
                }
                catch (IOException e)
                {
                        System.err.println("I/O error: " + e.getMessage());
                }
        }
}
