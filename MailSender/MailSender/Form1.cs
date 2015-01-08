using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Mail;
using System.Collections;

namespace MailSender
{
    public partial class Form1 : Form
    {
        private string login;
        private string serwer;
        private string odpowiedniSMTP;
        private int odpowiedniPort;
        private string[] arr;
        private ArrayList allAttachments = new ArrayList();
        private int ilosc = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void oProgramieToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Program do wysyłania e-maili.\nDariusz Ciechanowski 2012", "O programie");
        }

        private void wczytajToolStripMenuItem_Click(object sender, EventArgs e)
        {
            textBox4.Text = "Testowa wiadomość";
            richTextBox1.Text = "Cześć!\nPa!";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                MailMessage list = new MailMessage(textBox1.Text,
                                                   textBox3.Text,
                                                   textBox4.Text,
                                                   richTextBox1.Text);
                SmtpClient smtp1 = new SmtpClient(odpowiedniSMTP, odpowiedniPort);
                smtp1.UseDefaultCredentials = false;
                System.Net.NetworkCredential poswiadczenia = new System.Net.NetworkCredential(textBox1.Text, textBox2.Text);
                smtp1.Credentials = poswiadczenia;
                if (allAttachments.Count > 0)
                {
                    foreach (string attach in allAttachments)
                    {
                        Attachment attached = new Attachment(attach.Trim(), System.Net.Mime.MediaTypeNames.Application.Octet);
                        list.Attachments.Add(attached);
                    }
                }
                smtp1.Send(list);              
            }
            catch
            {
                MessageBox.Show("Błąd!");
            }
        }

        private void textBox1_Leave(object sender, EventArgs e)
        {
            if (textBox1.Text.Trim().Length == 0) return;
            int pos = textBox1.Text.IndexOf("@",0,textBox1.Text.Length);
            if (pos > 0)
            {
                string reszta = textBox1.Text.Substring(pos + 1, textBox1.Text.Length - (pos + 1));
                int pos2 = reszta.IndexOf(".", 0, reszta.Length);
                if ((pos2 > 0) && (pos2 != reszta.Length-1))
                {
                    login = textBox1.Text.Substring(0, pos);
                    serwer = reszta;
                    if ((serwer == "onet.pl") || (serwer == "vp.pl") || (serwer == "op.pl") || (serwer == "spoko.pl") || (serwer == "poczta.onet.pl") || (serwer == "onet.eu") || (serwer == "onet.com.pl") || (serwer == "opoczta.pl") || (serwer == "autograf.pl"))
                    {
                        if (textBox5.Text != "smtp.poczta.onet.pl")
                        {
                            if (MessageBox.Show("Znaleziono odpowiedni serwer SMTP. Użyć?", "SMTP", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                            {
                                odpowiedniSMTP = "smtp.poczta.onet.pl";
                                odpowiedniPort = 587;
                                textBox5.Text = odpowiedniSMTP;
                                textBox6.Text = odpowiedniPort.ToString();
                            }
                        }
                    }
                    if ((serwer == "wp.pl"))
                    {
                        if (textBox5.Text != "smtp.wp.pl")
                        {
                            if (MessageBox.Show("Znaleziono odpowiedni serwer SMTP. Użyć?", "SMTP", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                            {
                                odpowiedniSMTP = "smtp.wp.pl";
                                odpowiedniPort = 587;
                                textBox5.Text = odpowiedniSMTP;
                                textBox6.Text = odpowiedniPort.ToString();
                            }
                        }
                    }
                    if ((serwer == "interia.pl"))
                    {
                        if (textBox5.Text != "poczta.interia.pl")
                        {
                            if (MessageBox.Show("Znaleziono odpowiedni serwer SMTP. Użyć?", "SMTP", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                            {
                                odpowiedniSMTP = "poczta.interia.pl";
                                odpowiedniPort = 587;
                                textBox5.Text = odpowiedniSMTP;
                                textBox6.Text = odpowiedniPort.ToString();
                            }
                        }
                    }
                    if ((serwer == "interia.eu"))
                    {
                        if (textBox5.Text != "poczta.interia.eu")
                        {
                            if (MessageBox.Show("Znaleziono odpowiedni serwer SMTP. Użyć?", "SMTP", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                            {
                                odpowiedniSMTP = "poczta.interia.eu";
                                odpowiedniPort = 587;
                                textBox5.Text = odpowiedniSMTP;
                                textBox6.Text = odpowiedniPort.ToString();
                            }
                        }
                    }
                    if ((serwer == "gmail.com"))
                    {
                        if (textBox5.Text != "smtp.gmail.com")
                        {
                            if (MessageBox.Show("Znaleziono odpowiedni serwer SMTP. Użyć?", "SMTP", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                            {
                                odpowiedniSMTP = "smtp.gmail.com";
                                odpowiedniPort = 587;
                                textBox5.Text = odpowiedniSMTP;
                                textBox6.Text = odpowiedniPort.ToString();
                            }
                        }
                    }
                    if ((serwer == "o2.pl"))
                    {
                        if (textBox5.Text != "poczta.o2.pl")
                        {
                            if (MessageBox.Show("Znaleziono odpowiedni serwer SMTP. Użyć?", "SMTP", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                            {
                                odpowiedniSMTP = "poczta.o2.pl";
                                odpowiedniPort = 587;
                                textBox5.Text = odpowiedniSMTP;
                                textBox6.Text = odpowiedniPort.ToString();
                            }
                        }
                    }
                }
                else
                {
                    MessageBox.Show("Nieprawidołowy format e-maila.\nOczekiwano: [...]@[...].[...]", "Uwaga!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    textBox1.Focus();
                }
            }
            else
            {
                MessageBox.Show("Nieprawidołowy format e-maila.\nOczekiwano: [...]@[...].[...]", "Uwaga!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                textBox1.Focus();
            }
        }

        private void textBox3_Leave(object sender, EventArgs e)
        {
            if (textBox3.Text.Trim().Length == 0) return;
            int pos = textBox3.Text.IndexOf("@", 0, textBox3.Text.Length);
            if (pos > 0)
            {
                string reszta = textBox3.Text.Substring(pos + 1, textBox3.Text.Length - (pos + 1));
                int pos2 = reszta.IndexOf(".", 0, reszta.Length);
                if ((pos2 > 0) && (pos2 != reszta.Length - 1))
                {
                }
                else
                {
                    MessageBox.Show("Nieprawidołowy format e-maila.\nOczekiwano: [...]@[...].[...]", "Uwaga!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    textBox3.Focus();
                }
            }
            else
            {
                MessageBox.Show("Nieprawidołowy format e-maila.\nOczekiwano: [...]@[...].[...]", "Uwaga!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                textBox3.Focus();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                arr = openFileDialog1.FileNames;
                allAttachments.AddRange(arr);
                listBox1.Items.Clear();
                foreach (string s in allAttachments)
                {
                    listBox1.Items.Add(s + ";");
                }
                ilosc = listBox1.Items.Count;
                label7.Text = ilosc.ToString();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if ((listBox1.Items.Count > 0))
            {
                if ((listBox1.SelectedIndex > -1))
                {
                    allAttachments.RemoveAt(listBox1.SelectedIndex);
                    listBox1.Items.RemoveAt(listBox1.SelectedIndex);
                    ilosc = listBox1.Items.Count;
                    label7.Text = ilosc.ToString();
                    listBox1.SelectedIndex = -1;
                }
                else
                {
                    MessageBox.Show("Wybierz załącznik do usunięcia.", "Usuń załącznik");
                }
            }
            else
            {
                MessageBox.Show("Brak załączników do usunięcia.", "Usuń załącznik");
            }
        }

        private void sMTPIPortToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Dane wczytywane są automatycznie dla maili kończących się na:\nonet.pl\nvp.pl\nop.pl\nspoko.pl\npoczta.onet.pl\nonet.eu\nonet.com.pl\nopoczta.pl\nautograf.pl\nwp.pl\ninteria.pl\ninteria.eu\ngmail.com\no2.pl", "SMTP i port");
        }
    }
}
