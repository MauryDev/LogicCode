using ScintillaNET;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static LogicCodeIDE.Program;

namespace LogicCodeIDE
{
   
    public partial class Form1 : Form
    {
        static LogCallback action = new LogCallback(Debug_Log);
        static Form1 form;
        static List<string> txt = new List<string> {
            "bitset.len",
            "bitset.concat",
            // keywords
            "case",
            "const",
            "debug.log",
            "fun",
            "if",
            "int",
            "num",
            "ref",
            "return",
            "true",
            "false",
            "var",
            "while"
        };
        public Form1()
        {
            InitializeComponent();
        }
        static void Debug_Log(IntPtr text)
        {
            string textv = Marshal.PtrToStringAnsi(text);
            form.Invoke(new Action(() => { 
                form.label2.Text += textv;
            }));
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            form = this;
            Program.SetupLog(Marshal.GetFunctionPointerForDelegate(action));
            scintilla1.AutoCOrder = Order.PerformSort;
            scintilla1.Lexer = Lexer.Cpp;
            scintilla1.StyleResetDefault();
            scintilla1.Styles[Style.Default].Font = "Consolas";
            scintilla1.Styles[Style.Default].Size = 12;
            scintilla1.Styles[Style.Default].ForeColor = Color.White;
            scintilla1.Styles[Style.Default].BackColor = Color.Black;
            scintilla1.StyleClearAll();
            
            scintilla1.CaretForeColor = Color.White;
            scintilla1.Styles[Style.Cpp.Number].ForeColor = Color.LightGreen;
            scintilla1.Styles[Style.Cpp.String].ForeColor = Color.Orange;
            scintilla1.Styles[Style.Cpp.Word].ForeColor = Color.FromArgb(86, 156, 214);
            scintilla1.Styles[Style.Cpp.CommentLine].ForeColor = Color.Green;
            scintilla1.SetKeywords(0, "if fun while return const var case int num ref true");
        }

        private void scintilla1_CharAdded(object sender, CharAddedEventArgs e)
        {
            switch (e.Char)
            {
                case '(':
                    scintilla1.InsertText(scintilla1.CurrentPosition, ")");
                    return;
                case '@':
                    scintilla1.InsertText(scintilla1.CurrentPosition, "{}");
                    scintilla1.GotoPosition(scintilla1.CurrentPosition + 1);
                    return;
                case '"':
                    scintilla1.InsertText(scintilla1.CurrentPosition, "\"");
                    return;
                case '/':
                    scintilla1.InsertText(scintilla1.CurrentPosition, "/ ");
                    scintilla1.GotoPosition(scintilla1.CurrentPosition + 2);

                    return;
                case '\'':
                    scintilla1.InsertText(scintilla1.CurrentPosition, "'");
                    return;
            }
            // Find the word start

            var currentPos = scintilla1.CurrentPosition;
            var wordStartPos = scintilla1.WordStartPosition(currentPos, true);
            char f = (char)scintilla1.GetCharAt(wordStartPos);
            Console.WriteLine(f);
            // Display the autocompletion list
            var lenEntered = currentPos - wordStartPos;
            if (lenEntered > 0)
            {
                
                string text = scintilla1.GetTextRange(wordStartPos, lenEntered);
                string val = string.Join(" ",txt.Where((item) => item.StartsWith(text)));
                
                scintilla1.AutoCShow(lenEntered, val);

            }
        }
        static void RunScript(string str) {
            try
            {
                
                Program.runCode(str);

            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }

        }
        private void scintilla1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.F5)
            {
                RunScript(scintilla1.Text);
            }
        }

        private void scintilla1_KeyPress(object sender, KeyPressEventArgs e)
        {
            
            if (e.KeyChar < 32)
            {
                // Prevent control characters from getting inserted into the text buffer
                e.Handled = true;
                return;
            }
        }
    }
}
