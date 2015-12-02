using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace checker
{
    public partial class Form1 : Form
    {
        public int[] tags = new int[64];
        
        public Form1()
        {
            InitializeComponent();
            initialTags();
            AddPictureBox();
            
        }
        private int AiGo()
        {
            int n = 0;
            Random r = new Random();
            int iUp = 64;
            int iDown = -1;
            n = r.Next(iDown, iUp);
            while (tags[n] != 0)
            {
                r = new Random();
                iUp = 64;
                iDown = -1;
                n = r.Next(iDown, iUp);
            }
            return n;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            int n;
            n = Convert.ToInt32(inputText.Text);
            if (n >= 0 && n <= 63)
            {
                if (tags[n] == 0)
                {
                    tags[n] = 1;
                    PictureBox Pb = new PictureBox();
                    int i = n / 8;
                    int j = n % 8;




                    Pb.Height = 40;//每个格子高度 宽度均为70
                    Pb.Width = 40;//
                    Pb.Top = i * 40 + 40;//起始坐标
                    Pb.Left = 40 + j * 40;
                    Pb.BackColor = Color.Black;
                    this.Controls.Add(Pb);
                    Pb.BringToFront();

                    int nAi;
                    nAi=AiGo();
                    tags[nAi] = 1;
                    Pb = new PictureBox();
                    i = nAi / 8;
                    j = nAi % 8;




                    Pb.Height = 40;//每个格子高度 宽度均为70
                    Pb.Width = 40;//
                    Pb.Top = i * 40 + 40;//起始坐标
                    Pb.Left = 40 + j * 40;
                    Pb.BackColor = Color.Red;
                    this.Controls.Add(Pb);
                    Pb.BringToFront();

                }
                else
                {
                    MessageBox.Show("hehe");
                }
            }
            else
            {
                MessageBox.Show("hehe");
            }

        }
        public void initialTags()
        {
            for (int i = 0; i < 64; i++)
                tags[i] = 0;
        }
        //PictureBox[] Pb = new PictureBox[64];//构造棋盘用
        Label[] Lb = new Label[64];

        

        private void AddPictureBox()
        {
            int N = 0;
            for (int i = 0; i < 8; i++)//8
            {
                for (int j = 0; j < 8; j++)//8
                {
                    N = j + i * 8;
                    //Pb[N] = new PictureBox();//从第一列由上而下依次编号0到63,共64个格子
                    //Pb[N].Height = 40;//每个格子高度 宽度均为70
                    //Pb[N].Width = 40;//
                    //Pb[N].Top = i * 40 + 40;//起始坐标
                    //Pb[N].Left = 40+j * 40;//按行每次在窗体放置8个控件，然后在i+1；
                    Lb[N] = new Label();//从第一列由上而下依次编号0到63,共64个格子
                    Lb[N].Height = 40;//每个格子高度 宽度均为70
                    Lb[N].Width = 40;//
                    Lb[N].Top = i * 40 + 40;//起始坐标
                    Lb[N].Left = 40 + j * 40;//按行每次在窗体放置8个控件，然后在i+1；

                    if (i % 2 == j % 2)
                    {
                        //Pb[N].BackColor = Color.Green;//灰白间隔效果
                        Lb[N].Text = N.ToString();
                        Lb[N].BackColor = Color.Green;
                    }
                    else
                    {
                        //Pb[N].BackColor = Color.White;
                        Lb[N].Text = N.ToString();
                        Lb[N].BackColor = Color.White;
                    }
                    //this.Controls.Add(Pb[N]);//没有这个语句，控件是无法添加到窗体上的！
                    this.Controls.Add(Lb[N]);
                    Lb[N].BringToFront();
                }

            }


        }
    }
}
