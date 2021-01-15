/*
1242. Web Crawler Multithreaded



Given a url startUrl and an interface HtmlParser, implement a Multi-threaded web crawler to crawl all links that are under the same hostname as startUrl. 

Return all urls obtained by your web crawler in any order.

Your crawler should:

Start from the page: startUrl
Call HtmlParser.getUrls(url) to get all urls from a webpage of given url.
Do not crawl the same link twice.
Explore only the links that are under the same hostname as startUrl.


As shown in the example url above, the hostname is example.org. For simplicity sake, you may assume all urls use http protocol without any port specified. 
For example, the urls http://leetcode.com/problems and http://leetcode.com/contest are under the same hostname, while urls http://example.org/test and http://example.com/abc are not under the same hostname.

The HtmlParser interface is defined as such: 

interface HtmlParser {
  // Return a list of all urls from a webpage of given url.
  // This is a blocking call, that means it will do HTTP request and return when this request is finished.
  public List<String> getUrls(String url);
}
Note that getUrls(String url) simulates performing a HTTP request. You can treat it as a blocking function call which waits for a HTTP request to finish. 
It is guaranteed that getUrls(String url) will return the urls within 15ms.  Single-threaded solutions will exceed the time limit so, can your multi-threaded web crawler do better?

Below are two examples explaining the functionality of the problem, for custom testing purposes you'll have three variables urls, edges and startUrl. 
Notice that you will only have access to startUrl in your code, while urls and edges are not directly accessible to you in code.

 

Follow up:

Assume we have 10,000 nodes and 1 billion URLs to crawl. We will deploy the same software onto each node. The software can know about all the nodes. 
We have to minimize communication between machines and make sure each node does equal amount of work. How would your web crawler design change?
What if one node fails or does not work?
How do you know when the crawler is done?
 

Example 1:



Input:
urls = [
  "http://news.yahoo.com",
  "http://news.yahoo.com/news",
  "http://news.yahoo.com/news/topics/",
  "http://news.google.com",
  "http://news.yahoo.com/us"
]
edges = [[2,0],[2,1],[3,2],[3,1],[0,4]]
startUrl = "http://news.yahoo.com/news/topics/"
Output: [
  "http://news.yahoo.com",
  "http://news.yahoo.com/news",
  "http://news.yahoo.com/news/topics/",
  "http://news.yahoo.com/us"
]
Example 2:



Input: 
urls = [
  "http://news.yahoo.com",
  "http://news.yahoo.com/news",
  "http://news.yahoo.com/news/topics/",
  "http://news.google.com"
]
edges = [[0,2],[2,1],[3,2],[3,1],[3,0]]
startUrl = "http://news.google.com"
Output: ["http://news.google.com"]
Explanation: The startUrl links to all other pages that do not share the same hostname.
 

Constraints:

1 <= urls.length <= 1000
1 <= urls[i].length <= 300
startUrl is one of the urls.
Hostname label must be from 1 to 63 characters long, including the dots, may contain only the ASCII letters from 'a' to 'z', digits from '0' to '9' and the hyphen-minus character ('-').
The hostname may not start or end with the hyphen-minus character ('-'). 
See:  https://en.wikipedia.org/wiki/Hostname#Restrictions_on_valid_hostnames
You may assume there're no duplicates in url library.
*/
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <thread>
#include <mutex>

using std::unique_lock;
using std::thread;
using std::mutex;
using std::unordered_set;
using std::queue;
using std::vector;
using std::string;
using std::condition_variable;


// This is the HtmlParser's API interface.
// You should not implement it, or speculate about its implementation
class HtmlParser {
   public:
     vector<string> getUrls(string url) {
       return {};
     };
};

class WebCrawlerMultithread {

public:
    vector<string> crawl(string startUrl, HtmlParser& htmlParser) {

      auto getdomain = [](const string& url) -> string {

        if (url.length() < 8) return "";

        int index = url.find_first_of('/', 7);
        if (index == -1) index = url.length();

        return url.substr(7, index - 7);
      };


      string hostdomain = getdomain(startUrl);
      queue<string> qu{ {startUrl} };
      unordered_set<string> visited;
      visited.insert(startUrl);
      vector<string> ans;
      std::mutex mtx;

      auto update_qu = [&](const vector<string>& urls) {
        mtx.lock();
        for (auto c : urls) {
          if (visited.find(c) == visited.end()) {
            visited.insert(c);
            qu.push(c);
          }
        }
        mtx.unlock();
      };

      auto crawl_url = [&](const string& url) {
        vector<string> urls;
        for (auto child : htmlParser.getUrls(url)) {
          if (hostdomain == getdomain(child)) {
            urls.push_back(child);
          }
        }

        update_qu(urls);
      };

      while (!qu.empty()) {

        vector<thread> group;

        mtx.lock();

        int size = qu.size();

        while (size--) {

          auto url = qu.front();
          qu.pop();
          ans.push_back(url);

          group.push_back(thread(crawl_url, url));
        }

        mtx.unlock();

        for (thread& c : group)
          c.join();
      }

      return ans;
    }
};

class Solution {
private:
    int thread_num;
    string hostname;
    queue<string> q;
    unordered_set<string> seen;
    int working = 0;
    bool done;
    mutex m;
    condition_variable cv;
    
    string extractHostName(string& url){
        int start = url.find('/') + 2;
        int end =  url.find('/', start);
        if(end == string::npos) 
            return url.substr(start);
        return url.substr(start, end - start);
    }
    vector<thread> workers;
    
    // this a worker thread that will be doing tasks.
    void startWorker(HtmlParser* parser){
        while(true){
            unique_lock<mutex> ul(m);
            // wait until there are some tasks OR
            // we are done executing
            cv.wait(ul, [&](){
                return q.size() > 0 || done;
            });
            // if done, return.
            if(done)
                return;
            // indicate that this thread is in progress
            working++;
            string item = q.front(); q.pop();
            ul.unlock();
            // since getUrls can take a lot of time, release the lock.
            auto accessible = parser->getUrls(item);
            
            // acquire the lock and add tasks.
            ul.lock();
            for(auto& url : accessible){
                // if it has been seen already or the host name doesn't match, ignore it.
                if(seen.count(url) || extractHostName(url) != hostname)
                    continue;
                seen.insert(url);
                q.push(url);
            }
            working--;
            
            // IF 
            //   1) no thread is processing
            //   2) no tasks are available even after executing this task
            // THEN we are done.
            if(working == 0 && q.empty()){
                done = true;
            }
            // notify all the threads either about finishing or about availability of tasks.
            cv.notify_all();
        }
    }

public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        // get the hostname for this url.
        // mark it as seen.
        hostname = extractHostName(startUrl);
        seen.insert(startUrl);
        done = false;
        // get number of supported threads
        thread_num = thread::hardware_concurrency();
        // push the first task to do.
        q.push(startUrl);
        
        // start bunch of worker threads.
        for(int i = 0; i < thread_num; i++){
            workers.emplace_back(&Solution::startWorker, this, &htmlParser);
        }
        
        // join those threads so that crawl is a blocking call 
        for(auto &t : workers){
            t.join();
        }
        // return every unique processed string
        return vector<string>(seen.begin(), seen.end());
    }
};