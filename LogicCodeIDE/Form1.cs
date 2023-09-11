using MaterialSkin;
using MaterialSkin.Controls;
using ScintillaNET;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.IO.Pipes;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;
using static LogicCodeIDE.Program;
using static System.Net.Mime.MediaTypeNames;

namespace LogicCodeIDE
{

    public partial class Form1 : MaterialForm
    {

        static readonly LogCallback action = new LogCallback(Debug_Log);
        static readonly ClearCallback action2 = new ClearCallback(Debug_Clear);
        static Action<string> event1;
        static Action event2;

        static Form1 form;
        public Form1()
        {
            event1 = OnDebugLog;
            event2 = OnDebugClear;
            InitializeComponent();
        }

        static void Debug_Clear()
        {
            form.Invoke(event2);

        }
        void OnDebugClear()
        {
            materialLabel1.Text = "";
            var scroll = panel1.VerticalScroll;
            scroll.Value = scroll.Maximum;
        }

        static void Debug_Log(IntPtr text)
        {

            string textv = Marshal.PtrToStringAnsi(text);
            Debug_Log(textv);
        }
        static void Debug_Log(string textv)
        {
            form.Invoke(event1, textv);
        }
        void OnDebugLog(string txt)
        {
            form.materialLabel1.Text += txt;
            var scroll = form.panel1.VerticalScroll;
            scroll.Value = scroll.Maximum;
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            form = this;
            var materialSkinManager = MaterialSkinManager.Instance;
            materialSkinManager.AddFormToManage(this);

            materialSkinManager.Theme = MaterialSkinManager.Themes.DARK;
            materialLabel1.ForeColor = Color.White;

            Program.Setup_DebugLog(Marshal.GetFunctionPointerForDelegate(action));
            Program.Setup_DebugClear(Marshal.GetFunctionPointerForDelegate(action2));

            var maxLineNumberCharLength = scintilla1.Lines.Count.ToString().Length;
            Autocomplete.txt.Sort();
            const int padding = 2;
            scintilla1.Margins[0].Width = scintilla1.TextWidth(Style.LineNumber, new string('9', maxLineNumberCharLength + 1)) + padding;
            //scintilla1.AutoCOrder = Order;
            scintilla1.WordChars += ".$";
            scintilla1.StyleResetDefault();
            scintilla1.Styles[Style.Default].Font = "Roboto";
            scintilla1.Styles[Style.Default].Size = 12;
            scintilla1.Styles[Style.Default].ForeColor = Color.White;
            scintilla1.Styles[Style.Default].BackColor = Color.Black;



            scintilla1.StyleClearAll();

            scintilla1.Lexer = Lexer.Cpp;

            scintilla1.Styles[Style.LineNumber].ForeColor = Color.White;
            scintilla1.Styles[Style.LineNumber].BackColor = Color.Black;
            scintilla1.Styles[Style.LineNumber].Bold = true;

            scintilla1.CaretForeColor = Color.White;
            scintilla1.Styles[Style.Cpp.Number].ForeColor = Color.LightGreen;
            scintilla1.Styles[Style.Cpp.String].ForeColor = Color.Orange;
            scintilla1.Styles[Style.Cpp.Word].ForeColor = Color.FromArgb(86, 156, 214);
            scintilla1.Styles[Style.Cpp.CommentLine].ForeColor = Color.Green;
            scintilla1.SetKeywords(0, "if fun while return const var case int num ref true false none");


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
            // Display the autocompletion list
            var lenEntered = currentPos - wordStartPos;
            if (lenEntered > 0)
            {

                string text = scintilla1.GetTextRange(wordStartPos, lenEntered);
                string val = string.Join(" ", Autocomplete.txt.Where((item) => item.StartsWith(text)));

                scintilla1.AutoCShow(lenEntered, val);

            }
        }
        static void RunScript()
        {
            try
            {
                Debug_Clear();
                Stopwatch watch = Stopwatch.StartNew();
                Program.runCode(form.scintilla1.Text);
                watch.Stop();
                Debug_Log("Execution Time: " + watch.ElapsedMilliseconds + "ms");
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }

        }
        void LoadFile()
        {
            var result = openFileDialog1.ShowDialog();
            if (result == DialogResult.OK)
            {
                var fileStream = openFileDialog1.OpenFile();
                using (StreamReader reader = new StreamReader(fileStream))
                {
                    scintilla1.Text = reader.ReadToEnd();
                }
            }
        }
        void SaveFile()
        {
            var result = saveFileDialog1.ShowDialog();
            if (result == DialogResult.OK)
            {
                var fileStream = saveFileDialog1.OpenFile();
                using (var reader = new StreamWriter(fileStream))
                {
                    reader.Write(scintilla1.Text);
                }
            }
        }
        private void scintilla1_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.F5:
                    {
                        var thread = new Thread(RunScript);
                        thread.Start();
                        break;
                    }
                    
                case Keys.F6:
                    LoadFile();
                    break;
                case Keys.F7:
                    SaveFile();
                    break;
            }
        }

        private void scintilla1_KeyPress(object sender, KeyPressEventArgs e)
        {

            if (e.KeyChar < 32)
            {
                e.Handled = true;
                return;
            }
        }

        private void scintilla1_TextChanged(object sender, EventArgs e)
        {
            var maxLineNumberCharLength = scintilla1.Lines.Count.ToString().Length;

            const int padding = 2;
            scintilla1.Margins[0].Width = scintilla1.TextWidth(Style.LineNumber, new string('9', maxLineNumberCharLength + 1)) + padding;
        }

        private void materialRaisedButton1_Click(object sender, EventArgs e)
        {
            
            var thread = new Thread(RunScript);
            thread.Start();
        }

        private void materialRaisedButton2_Click(object sender, EventArgs e)
        {
            LoadFile();
        }

        private void materialRaisedButton3_Click(object sender, EventArgs e)
        {
            SaveFile();
        }
    }
}
