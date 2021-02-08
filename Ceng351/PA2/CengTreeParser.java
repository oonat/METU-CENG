import java.io.IOException;
import java.util.ArrayList;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class CengTreeParser {
    public static ArrayList<CengVideo> parseVideosFromFile(String filename) {
        ArrayList<CengVideo> videoList = new ArrayList<CengVideo>();

        // You need to parse the input file in order to use GUI tables.
        // TODO: Parse the input file, and convert them into CengVideos

        // init scanner
        Scanner scanner = null;
        String line_to_read;

        try {
            File input_file = new File(filename);
            scanner = new Scanner(input_file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        while (scanner.hasNextLine()) {
            line_to_read = scanner.nextLine();
            String[] tmp = line_to_read.split("[|]");

            Integer key = Integer.parseInt(tmp[0]);
            String videoTitle = tmp[1];
            String channelName = tmp[2];
            String category = tmp[3];

            CengVideo cengvid = new CengVideo(key, videoTitle, channelName, category);
            videoList.add(cengvid);
        }

        return videoList;
    }

    public static void startParsingCommandLine() throws IOException {
        // DONE: Start listening and parsing command line -System.in-.
        // There are 4 commands:
        // 1) quit : End the app, gracefully. Print nothing, call nothing, just break off your command line loop.
        // 2) add : Parse and create the video, and call CengVideoRunner.addVideo(newlyCreatedVideo).
        // 3) search : Parse the key, and call CengVideoRunner.searchVideo(parsedKey).
        // 4) print : Print the whole tree, call CengVideoRunner.printTree().

        // Commands (quit, add, search, print) are case-insensitive.

        Scanner scanner = new Scanner(System.in);
        String input;
        String inp_command;

        while(true) {
            input = scanner.nextLine();
            String[] inp_array = input.split("[|]");
            inp_command = inp_array[0];

            if(inp_command.equalsIgnoreCase("quit"))
                return;

            if(inp_command.equalsIgnoreCase("add")){
                Integer key = Integer.parseInt(inp_array[1]);
                String videoTitle = inp_array[2];
                String channelName = inp_array[3];
                String category = inp_array[4];
                CengVideo cengvid = new CengVideo(key, videoTitle, channelName, category);

                CengVideoRunner.addVideo(cengvid);

            }else if(inp_command.equalsIgnoreCase("search")){
                Integer key = Integer.parseInt(inp_array[1]);
                CengVideoRunner.searchVideo(key);

            }else if(inp_command.equalsIgnoreCase("print")) {
                CengVideoRunner.printTree();
            }

        }

    }

}
