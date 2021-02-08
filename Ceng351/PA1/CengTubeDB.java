package ceng.ceng351.cengtubedb;

import java.sql.*;
import java.util.ArrayList;

public class CengTubeDB implements ICengTubeDB{
        /**
         * Place your initialization code inside if required.
         *
         * This function will be called before all other operations. If your implementation
         * needs initialization, necessary operations should be done inside this function. For
         * example, you can set your connection to the database server inside this function.
         */
        private static String user = "e231039";
        private static String password = "e41a4671";
        private static String database = "db231039";
        private static String host = "144.122.71.168";
        private static int port = 3306;

        private static Connection connection = null;

        @Override
        public void initialize(){

                String url = "jdbc:mysql://" + this.host + ":" + this.port + "/" + this.database + "?useSSL=false";

                try {
                        Class.forName("com.mysql.cj.jdbc.Driver");
                        this.connection =  DriverManager.getConnection(url, this.user, this.password);
                } catch (SQLException | ClassNotFoundException e) {
                        e.printStackTrace();
                }


        }


        /**
         * Should create the necessary tables.
         *
         * @return the number of tables that are created successfully.
         */
        @Override
        public int createTables(){

                int number_of_tables_created = 0;

                String query_create_User = "CREATE TABLE IF NOT EXISTS User(" +
                        "userID INT NOT NULL, " +
                        "userName VARCHAR(30), " +
                        "email VARCHAR(30), " +
                        "password VARCHAR(30), " +
                        "status VARCHAR(15), " +
                        "PRIMARY KEY (userID));";

                String query_create_Video = "CREATE TABLE IF NOT EXISTS Video(" +
                        "videoID INT NOT NULL, " +
                        "userID INT, " +
                        "videoTitle VARCHAR(60), " +
                        "likeCount INT, " +
                        "dislikeCount INT, " +
                        "datePublished DATE, " +
                        "FOREIGN KEY (userID) REFERENCES User(userID) " +
                                "ON DELETE CASCADE, " +
                        "PRIMARY KEY (videoID));";

                String query_create_Comment = "CREATE TABLE IF NOT EXISTS Comment(" +
                        "commentID INT NOT NULL, " +
                        "userID INT, " +
                        "videoID INT, " +
                        "commentText VARCHAR(1000), " +
                        "dateCommented DATE, " +
                        "FOREIGN KEY (userID) REFERENCES User(userID) " +
                                "ON DELETE SET NULL, " +
                        "FOREIGN KEY (videoID) REFERENCES Video(videoID) " +
                                "ON DELETE CASCADE, " +
                        "PRIMARY KEY (commentID));";

                String query_create_Watch = "CREATE TABLE IF NOT EXISTS Watch(" +
                        "userID INT NOT NULL, " +
                        "videoID INT NOT NULL, " +
                        "dateWatched DATE, " +
                        "FOREIGN KEY (userID) REFERENCES User(userID) " +
                                "ON DELETE CASCADE, " +
                        "FOREIGN KEY (videoID) REFERENCES Video(videoID) " +
                                "ON DELETE CASCADE, " +
                        "PRIMARY KEY (userID, videoID));";


                // User Table
                try{
                        Statement statement = this.connection.createStatement();
                        statement.executeUpdate(query_create_User);
                        number_of_tables_created++;
                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                // Video Table
                try{
                        Statement statement = this.connection.createStatement();
                        statement.executeUpdate(query_create_Video);
                        number_of_tables_created++;
                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                // Comment Table
                try{
                        Statement statement = this.connection.createStatement();
                        statement.executeUpdate(query_create_Comment);
                        number_of_tables_created++;
                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                // Watch Table
                try{
                        Statement statement = this.connection.createStatement();
                        statement.executeUpdate(query_create_Watch);
                        number_of_tables_created++;
                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                return number_of_tables_created;
        }


        /**
         * Should drop the tables if exists.
         *
         * @return the number of tables that are dropped successfully.
         */
        @Override
        public int dropTables(){

                int number_of_tables_dropped = 0;

                String query_drop_User = "DROP TABLE IF EXISTS User;";
                String query_drop_Video = "DROP TABLE IF EXISTS Video;";
                String query_drop_Comment = "DROP TABLE IF EXISTS Comment;";
                String query_drop_Watch = "DROP TABLE IF EXISTS Watch;";

                // DUE TO THE FOREIGN KEY CONSTRAINTS YOU HAVE TO DROP THE TABLES IN REVERSE ORDER !!!


                // Watch Table
                try{
                        Statement statement = this.connection.createStatement();
                        statement.executeUpdate(query_drop_Watch);
                        number_of_tables_dropped++;
                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                // Comment Table
                try{
                        Statement statement = this.connection.createStatement();
                        statement.executeUpdate(query_drop_Comment);
                        number_of_tables_dropped++;
                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                // Video Table
                try{
                        Statement statement = this.connection.createStatement();
                        statement.executeUpdate(query_drop_Video);
                        number_of_tables_dropped++;
                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                // User Table
                try{
                        Statement statement = this.connection.createStatement();
                        statement.executeUpdate(query_drop_User);
                        number_of_tables_dropped++;
                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                // close the db connection
                try {
                        this.connection.close();
                } catch (SQLException e) {
                        e.printStackTrace();
                }

                return number_of_tables_dropped;

        }


        /**
         * Should insert an array of User into the database.
         *
         * @return Number of rows inserted successfully.
         */
        @Override
        public int insertUser(User[] users){

                int number_of_users_records = 0;
                String insert_query = "INSERT INTO User(" +
                        "userID, " +
                        "userName, " +
                        "email, " +
                        "password, " +
                        "status) VALUES (?, ?, ?, ?, ?);";

                for(int i = 0; i < users.length; i++){

                        User target = users[i];

                        try{
                                PreparedStatement prep_statement = this.connection.prepareStatement(insert_query);
                                prep_statement.setInt(1, target.userID);
                                prep_statement.setString(2, target.userName);
                                prep_statement.setString(3, target.email);
                                prep_statement.setString(4, target.password);
                                prep_statement.setString(5, target.status);
                                prep_statement.executeUpdate();
                                number_of_users_records++;
                                prep_statement.close();
                        }catch (SQLException e) {
                                e.printStackTrace();
                        }

                }

                return number_of_users_records;
        }

        /**
         * Should insert an array of Video into the database.
         *
         * @return Number of rows inserted successfully.
         */
        @Override
        public int insertVideo(Video[] videos){

                int number_of_videos_records = 0;
                String insert_query = "INSERT INTO Video(" +
                        "videoID, " +
                        "userID, " +
                        "videoTitle, " +
                        "likeCount, " +
                        "dislikeCount, " +
                        "datePublished) VALUES (?, ?, ?, ?, ?, ?);";

                for(int i = 0; i < videos.length; i++){

                        Video target = videos[i];

                        try{
                                PreparedStatement prep_statement = this.connection.prepareStatement(insert_query);
                                prep_statement.setInt(1, target.videoID);
                                prep_statement.setInt(2, target.userID);
                                prep_statement.setString(3, target.videoTitle);
                                prep_statement.setInt(4, target.likeCount);
                                prep_statement.setInt(5, target.dislikeCount);
                                prep_statement.setString(6, target.datePublished);
                                prep_statement.executeUpdate();
                                number_of_videos_records++;
                                prep_statement.close();
                        }catch (SQLException e) {
                                e.printStackTrace();
                        }

                }

                return number_of_videos_records;

        }

        /**
         * Should insert an array of Comment into the database.
         *
         * @return Number of rows inserted successfully.
         */
        @Override
        public int insertComment(Comment[] comments){

                int number_of_comments_records = 0;
                String insert_query = "INSERT INTO Comment(" +
                        "commentID, " +
                        "userID, " +
                        "videoID, " +
                        "commentText, " +
                        "dateCommented) VALUES (?, ?, ?, ?, ?);";

                for(int i = 0; i < comments.length; i++){

                        Comment target = comments[i];

                        try{
                                PreparedStatement prep_statement = this.connection.prepareStatement(insert_query);
                                prep_statement.setInt(1, target.commentID);
                                prep_statement.setInt(2, target.userID);
                                prep_statement.setInt(3, target.videoID);
                                prep_statement.setString(4, target.commentText);
                                prep_statement.setString(5, target.dateCommented);
                                prep_statement.executeUpdate();
                                number_of_comments_records++;
                                prep_statement.close();
                        }catch (SQLException e) {
                                e.printStackTrace();
                        }

                }

                return number_of_comments_records;

        }

        /**
         * Should insert an array of Watch into the database.
         *
         * @return Number of rows inserted successfully.
         */
        @Override
        public int insertWatch(Watch[] watchEntries){

                int number_of_watch_records = 0;
                String insert_query = "INSERT INTO Watch(" +
                        "userID, " +
                        "videoID, " +
                        "dateWatched) VALUES (?, ?, ?);";

                for(int i = 0; i < watchEntries.length; i++){

                        Watch target = watchEntries[i];

                        try{
                                PreparedStatement prep_statement = this.connection.prepareStatement(insert_query);
                                prep_statement.setInt(1, target.userID);
                                prep_statement.setInt(2, target.videoID);
                                prep_statement.setString(3, target.dateWatched);
                                prep_statement.executeUpdate();
                                number_of_watch_records++;
                                prep_statement.close();
                        }catch (SQLException e) {
                                e.printStackTrace();
                        }

                }

                return number_of_watch_records;

        }


        /**
         * Get videos which have higher likeCount than dislikeCount
         *
         * @return QueryResult.VideoTitleLikeCountDislikeCountResult[]
         */
        @Override
        public QueryResult.VideoTitleLikeCountDislikeCountResult[] question3(){

                ArrayList<QueryResult.VideoTitleLikeCountDislikeCountResult> tmp_array = new ArrayList<>();
                ResultSet res;

                String get_query = "SELECT DISTINCT v.videoTitle, v.likeCount, v.dislikeCount " +
                        "FROM Video v " +
                        "WHERE v.likeCount > v.dislikeCount " +
                        "ORDER BY v.videoTitle ASC;";

                try{
                        Statement statement = this.connection.createStatement();
                        res = statement.executeQuery(get_query);

                        while(res.next()){
                                String title = res.getString("videoTitle");
                                int like_count = res.getInt("likeCount") ;
                                int dislike_count = res.getInt("dislikeCount");
                                tmp_array.add(new QueryResult.VideoTitleLikeCountDislikeCountResult(
                                        title, like_count, dislike_count));
                        }

                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                QueryResult.VideoTitleLikeCountDislikeCountResult[] video_array =
                        new QueryResult.VideoTitleLikeCountDislikeCountResult[tmp_array.size()];

                for(int i = 0; i < tmp_array.size(); i++){
                        video_array[i] = tmp_array.get(i);
                }

                return video_array;
        }

        /**
         * Get the videos commented by the given userID
         *
         * @param userID given userID
         *
         * @return QueryResult.VideoTitleUserNameCommentTextResult[]
         */
        @Override
        public QueryResult.VideoTitleUserNameCommentTextResult[] question4(Integer userID){


                ArrayList<QueryResult.VideoTitleUserNameCommentTextResult> tmp_array = new ArrayList<>();
                ResultSet res;

                String get_query = "SELECT DISTINCT v.videoTitle, u.userName, c.commentText " +
                        "FROM Video v, Comment c, User u " +
                        "WHERE c.userID = " + userID + " AND u.userID = " + userID + " AND  v.videoID = c.videoID " +
                        "ORDER BY v.videoTitle ASC;";

                try{
                        Statement statement = this.connection.createStatement();
                        res = statement.executeQuery(get_query);

                        while(res.next()){
                                String title = res.getString("videoTitle");
                                String user_name = res.getString("userName") ;
                                String comment_text = res.getString("commentText");
                                tmp_array.add(new QueryResult.VideoTitleUserNameCommentTextResult(
                                        title, user_name, comment_text));
                        }

                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                QueryResult.VideoTitleUserNameCommentTextResult[] video_array =
                        new QueryResult.VideoTitleUserNameCommentTextResult[tmp_array.size()];

                for(int i = 0; i < tmp_array.size(); i++){
                        video_array[i] = tmp_array.get(i);
                }

                return video_array;


        }

        /**
         * Find the oldest published video for a given userID which doesn’t contain ”VLOG" in its title
         *
         * @param userID given userID
         * @return QueryResult.VideoTitleUserNameDatePublishedResult[]
         */
        @Override
        public QueryResult.VideoTitleUserNameDatePublishedResult[] question5(Integer userID){


                ArrayList<QueryResult.VideoTitleUserNameDatePublishedResult> tmp_array = new ArrayList<>();
                ResultSet res;

                String get_query = "SELECT DISTINCT v.videoTitle, u.userName, v.datePublished " +
                        "FROM Video v, User u " +
                        "WHERE v.userID = " + userID + " AND u.userID = " + userID + " AND  v.datePublished = " +
                                "(SELECT MIN(v2.datePublished) " +
                                "FROM Video v2 " +
                                "WHERE v2.userID = " + userID + " AND v2.videoTitle NOT LIKE '%VLOG%') " +
                        "ORDER BY v.videoTitle ASC;";

                try{
                        Statement statement = this.connection.createStatement();
                        res = statement.executeQuery(get_query);

                        if(res.next()){
                                String title = res.getString("videoTitle");
                                String user_name = res.getString("userName") ;
                                String date_published = res.getString("datePublished");
                                tmp_array.add(new QueryResult.VideoTitleUserNameDatePublishedResult(
                                        title, user_name, date_published));
                        }

                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                QueryResult.VideoTitleUserNameDatePublishedResult[] video_array =
                        new QueryResult.VideoTitleUserNameDatePublishedResult[tmp_array.size()];

                for(int i = 0; i < tmp_array.size(); i++){
                        video_array[i] = tmp_array.get(i);
                }

                return video_array;
        }


        /**
         * Get the trending top three videos for a given time interval
         *
         * YOU SHOULD INCLUDE dateStart and dateEnd in the result, it is a CLOSED interval.
         *
         * @param dateStart start date of the interval
         * @param dateEnd end date of the interval
         *
         * @return QueryResult.VideoTitleUserNameNumOfWatchResult[]
         */
        @Override
        public QueryResult.VideoTitleUserNameNumOfWatchResult[] question6(String dateStart, String dateEnd){

                ArrayList<QueryResult.VideoTitleUserNameNumOfWatchResult> tmp_array = new ArrayList<>();
                ResultSet res;

                String get_query = "SELECT DISTINCT v.videoTitle, u.userName, COUNT(*) AS num_of_watch " +
                        "FROM Video v, User u, Watch w " +
                        "WHERE w.videoID = v.videoID AND v.userID = u.userID " +
                        "AND  v.datePublished >= \"" + dateStart +
                        "\" AND v.datePublished <= \"" + dateEnd + "\" " +
                        "GROUP BY v.videoID, v.videoTitle, u.userName " +
                        "ORDER BY COUNT(*) DESC " +
                        "LIMIT 3 ;";

                try{
                        Statement statement = this.connection.createStatement();
                        res = statement.executeQuery(get_query);

                        while(res.next()){
                                String video_title = res.getString("videoTitle");
                                String user_name = res.getString("userName") ;
                                int num_of_watch = res.getInt("num_of_watch");
                                tmp_array.add(new QueryResult.VideoTitleUserNameNumOfWatchResult(
                                        video_title, user_name, num_of_watch));
                        }


                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                QueryResult.VideoTitleUserNameNumOfWatchResult[] video_array =
                        new QueryResult.VideoTitleUserNameNumOfWatchResult[tmp_array.size()];

                for(int i = 0; i < tmp_array.size(); i++){
                        video_array[i] = tmp_array.get(i);
                }

                return video_array;

        }


        /**
         * Get users and the number of videos watched only by her/him.
         *
         *
         * @return QueryResult.UserIDUserNameEmailResult[]
         */
        @Override
        public QueryResult.UserIDUserNameNumOfVideosWatchedResult[] question7(){
                ArrayList<QueryResult.UserIDUserNameNumOfVideosWatchedResult> tmp_array = new ArrayList<>();
                ResultSet res;

                String get_query = "SELECT DISTINCT u.userID, u.userName, COUNT(*) AS num_of_watch " +
                        "FROM User u, Watch w " +
                        "WHERE u.userID = w.userID AND " +
                        "NOT EXISTS " +
                                "(SELECT * FROM Watch w2 " +
                                "WHERE w2.videoID = w.videoID AND w2.userID <> w.userID) " +
                        "GROUP BY u.userID, u.userName " +
                        "ORDER BY u.userID ASC;";

                try{
                        Statement statement = this.connection.createStatement();
                        res = statement.executeQuery(get_query);

                        while(res.next()){
                                int user_id = res.getInt("userID");
                                String user_name = res.getString("userName") ;
                                int num_of_watch = res.getInt("num_of_watch");
                                tmp_array.add(new QueryResult.UserIDUserNameNumOfVideosWatchedResult(
                                        user_id, user_name, num_of_watch));
                        }


                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                QueryResult.UserIDUserNameNumOfVideosWatchedResult[] user_array =
                        new QueryResult.UserIDUserNameNumOfVideosWatchedResult[tmp_array.size()];

                for(int i = 0; i < tmp_array.size(); i++){
                        user_array[i] = tmp_array.get(i);
                }

                return user_array;
        }


        /**
         * Get users who have watched and commented all of their own videos
         *
         * @return QueryResult.UserIDUserNameEmailResult[]
         */
        @Override
        public QueryResult.UserIDUserNameEmailResult[]  question8(){

                ArrayList<QueryResult.UserIDUserNameEmailResult> tmp_array = new ArrayList<>();
                ResultSet res;

                String get_query = "SELECT DISTINCT u.userID, u.userName, u.email " +
                        "FROM User u, Video v " +
                        "WHERE v.userID = u.userID AND NOT EXISTS " +
                                "(SELECT DISTINCT v1.videoID " +
                                        "FROM Video v1 " +
                                        "WHERE v1.userID = u.userID AND v1.videoID NOT IN " +
                                                "(SELECT DISTINCT w.videoID " +
                                                        "FROM Watch w " +
                                                        "WHERE w.userID = u.userID)) " +
                        "AND NOT EXISTS " +
                                "(SELECT DISTINCT v2.videoID " +
                                        "FROM Video v2 " +
                                        "WHERE v2.userID = u.userID AND v2.videoID NOT IN " +
                                                "(SELECT DISTINCT c.videoID " +
                                                        "FROM Comment c " +
                                                        "WHERE c.userID = u.userID)) " +
                        "ORDER BY u.userID ASC;";

                try{
                        Statement statement = this.connection.createStatement();
                        res = statement.executeQuery(get_query);

                        while(res.next()){
                                int user_id = res.getInt("userID");
                                String user_name = res.getString("userName") ;
                                String email = res.getString("email");
                                tmp_array.add(new QueryResult.UserIDUserNameEmailResult(
                                        user_id, user_name, email));
                        }

                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                QueryResult.UserIDUserNameEmailResult[] user_array =
                        new QueryResult.UserIDUserNameEmailResult[tmp_array.size()];

                for(int i = 0; i < tmp_array.size(); i++){
                        user_array[i] = tmp_array.get(i);
                }

                return user_array;

        }

        /**
         * Get users that has at least one watch but no comments
         *
         * @return QueryResult.UserIDUserNameEmailResult[]
         */
        @Override
        public QueryResult.UserIDUserNameEmailResult[]  question9(){

                ArrayList<QueryResult.UserIDUserNameEmailResult> tmp_array = new ArrayList<>();
                ResultSet res;

                String get_query = "SELECT DISTINCT u.userID, u.userName, u.email " +
                        "FROM User u " +
                        "WHERE EXISTS (SELECT * FROM Watch w WHERE w.userID = u.userID) AND " +
                        "NOT EXISTS (SELECT * FROM Comment c WHERE c.userID = u.userID) " +
                        "ORDER BY u.userID ASC;";

                try{
                        Statement statement = this.connection.createStatement();
                        res = statement.executeQuery(get_query);

                        while(res.next()){
                                int user_id = res.getInt("userID");
                                String user_name = res.getString("userName") ;
                                String email = res.getString("email");
                                tmp_array.add(new QueryResult.UserIDUserNameEmailResult(
                                        user_id, user_name, email));
                        }

                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                QueryResult.UserIDUserNameEmailResult[] user_array =
                        new QueryResult.UserIDUserNameEmailResult[tmp_array.size()];

                for(int i = 0; i < tmp_array.size(); i++){
                        user_array[i] = tmp_array.get(i);
                }

                return user_array;

        }

        /**
         *  Update the users’ status to ”verified” if the view count of all their videos in total is more than the given number
         *
         * @param givenViewCount the threshold to use in the query
         *
         * @return int return the number of rows affected
         */
        @Override
        public int question10(int givenViewCount){
                String update_query = "UPDATE User u " +
                        "SET u.status = \"verified\" " +
                        "WHERE " + givenViewCount + " < " +
                        "(SELECT COUNT(*) " +
                        "FROM Watch w, Video v " +
                        "WHERE w.videoID = v.videoID AND v.userID = u.userID);";

                int number_of_updates = 0;

                try{
                        Statement statement = this.connection.createStatement();
                        number_of_updates = statement.executeUpdate(update_query);

                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                return number_of_updates;


        }

        /**
         *  Given a video id and a string, update the title of the video with the given id to the new string
         *
         * @param videoID the identifier for the video to be updated
         * @param newTitle the new title that will replace the old one
         *
         * @return int return the number of rows affected
         */
        @Override
        public int question11(Integer videoID, String newTitle){

                String update_query = "UPDATE Video v " +
                        "SET v.videoTitle = \"" + newTitle + "\" " +
                        "WHERE v.videoID = " + videoID + ";";

                int number_of_updates = 0;

                try{
                        Statement statement = this.connection.createStatement();
                        number_of_updates = statement.executeUpdate(update_query);

                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                return number_of_updates;

        }

        /**
         *   Delete the video(s) with the given video title.
         *
         * @param videoTitle
         *
         * @return int return the number of rows in the Video table after delete operation
         */
        @Override
        public int question12(String videoTitle){

                String delete_query = "DELETE FROM Video " +
                        "WHERE videoTitle = \"" + videoTitle + "\" ;";


                try{
                        Statement statement = this.connection.createStatement();
                        statement.executeUpdate(delete_query);
                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }


                String get_query = "SELECT COUNT(*) AS row_count FROM Video;";
                int number_of_rows_after_delete = 0;
                ResultSet res;

                try{
                        Statement statement = this.connection.createStatement();
                        res = statement.executeQuery(get_query);
                        res.next();

                        number_of_rows_after_delete = res.getInt("row_count");

                        statement.close();
                }catch (SQLException e) {
                        e.printStackTrace();
                }

                return number_of_rows_after_delete;

        }


}
