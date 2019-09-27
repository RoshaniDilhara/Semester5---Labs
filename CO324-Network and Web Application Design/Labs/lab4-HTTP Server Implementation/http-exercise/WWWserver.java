
import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class WWWserver extends Thread {

	static final int PORT = 4321;

	final Socket socket;

	public WWWserver(Socket s) {
		this.socket = s;
	}
	
	@Override
	public void run() {
		try (Scanner sin = new Scanner(socket.getInputStream() ); 
			PrintStream sout = new PrintStream(socket.getOutputStream()) )  {
			Request r= new Request(sin);
			System.err.println("Got request:\n" + r);

			/* create a new response according to the request. 
			and send it back to the client. Use the methods provided in FileOp class to get the file status info */
			
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				socket.close();
			} catch (IOException e) {}
		}
	}
	
	public static void main(String[] args) throws IOException {		
		try( ServerSocket ss = new ServerSocket(PORT)) {		
			while (true) {
				Socket socket = ss.accept(); 
				new WWWserver(socket).start();			 
			}
		}
	}
	
}
