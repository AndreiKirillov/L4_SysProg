using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Threading;
using System.IO;
using System.Runtime.InteropServices;

namespace Kirillov_lab1_sharp
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct header            
    {
        [MarshalAs(UnmanagedType.I4)]
        public int event_code;
        [MarshalAs(UnmanagedType.I4)]
        public int thread_id;
        [MarshalAs(UnmanagedType.I4)]
        public int message_size;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct confirm_header
    {
        [MarshalAs(UnmanagedType.I4)]
        public int confirm_status;
        [MarshalAs(UnmanagedType.I4)]
        public int threads_count;
    };

    public partial class Form1 : Form
    {
        // подключаем dll функции для связи с сервером

        [DllImport("FileMapping.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        private static extern bool ConnectToServer();

        [DllImport("FileMapping.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        private static extern bool SendMessageToServer(StringBuilder message, ref header h);

        [DllImport("FileMapping.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        private static extern confirm_header WaitForConfirm();

        [DllImport("FileMapping.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        private static extern void CheckServer();

        private int count_threads = 0;
        private bool is_connected = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void btn_connect_Click(object sender, EventArgs e)
        {
            if (!is_connected)
            {
                if (ConnectToServer())          // Подключаемся к серверу
                {
                    CheckServer();
                    confirm_header server_answer = WaitForConfirm();
                    if(server_answer.confirm_status == 1)
                    {
                        is_connected = true;

                        listbox_threads.Items.Add("Все потоки");
                        listbox_threads.Items.Add("Главный поток");
                        for(int num = 0; num < server_answer.threads_count; num++)
                            listbox_threads.Items.Add($"{++count_threads}-й поток");
                    }
                    else
                    {
                        MessageBox.Show("Не удалось подключиться к серверу!");
                        return;
                    }
                }
                else 
                {
                    MessageBox.Show("Не удалось подключиться к серверу!");
                    return;
                }
            }
            else
            {
                MessageBox.Show("Вы уже подключены к серверу!");
                return;
            }
        }

        private void btn_start_Click(object sender, EventArgs e)
        {
            //if(!is_connected)
            //{
            //    listbox_threads.Items.Clear();
            //    count_threads = 0;
            //    if (textBox_Nthreads.TextLength == 0)
            //    {
            //        MessageBox.Show("Внимание! Задайте количество создаваемых потоков!");
            //        return;
            //    }
                
            //    listbox_threads.Items.Add("Все потоки");
            //    listbox_threads.Items.Add("Главный поток");
            //    int nThreads = Convert.ToInt32(textBox_Nthreads.Text);
            //    if (confirmEvent.WaitOne())
            //        if (nThreads > 0)
            //        {
            //            for (int i = 0; i < nThreads; i++)
            //            {
            //                //WriteToChild()
            //                startEvent.Set();
            //                if(confirmEvent.WaitOne(-1))
            //                    listbox_threads.Items.Add($"{++count_threads}-й поток");
            //            }
            //        }
            //}
            //else
            //{
            //    if (textBox_Nthreads.TextLength == 0)
            //    {
            //        MessageBox.Show("Внимание! Задайте количество создаваемых потоков!");
            //        return;
            //    }
            //    int nThreads = Convert.ToInt32(textBox_Nthreads.Text);
            //    if (nThreads > 0)
            //    {
            //        for (int i = 0; i < nThreads; i++)
            //        { 
            //            startEvent.Set();
            //            confirmEvent.WaitOne();
            //            listbox_threads.Items.Add($"{++count_threads}-й поток");
            //        }
            //    }
            //}
            
        }

        private void btn_stop_Click(object sender, EventArgs e)
        {
            //if (child_process != null)
            //{
            //    stopEvent.Set();
            //    if(count_threads == 0)
            //    {                                      // событие закрытия дочерней программы
            //        if (closeProgrammEvent.WaitOne())
            //        {
            //            listbox_threads.Items.Clear();
            //            count_threads = 0;
            //            child_process.Close();
            //            child_process = null;
            //        }
            //    }
            //    else                                  // лишь завершение потока
            //    {
            //        if (confirmEvent.WaitOne())
            //        {
            //            listbox_threads.Items.RemoveAt(count_threads + 1);
            //            --count_threads;
            //        }
            //    }
            //}
            //else 
            //{
            //    MessageBox.Show("Ошибка! Дочерняя программа не запущена!");
            //}
        }

        private void btn_send_Click(object sender, EventArgs e)
        {
            //if (child_process != null)
            //{
            //    if (textBox_Message.TextLength == 0)
            //    {
            //        MessageBox.Show("Внимание! Напишите текст сообщения!");
            //        return;
            //    }
            //    if(listbox_threads.SelectedIndex < 0)
            //    {
            //        MessageBox.Show("Внимание! Выберете поток!");
            //        return;
            //    }

            //    StringBuilder message = new StringBuilder(textBox_Message.Text);
            //    header h = new header();
            //    h.thread_id = listbox_threads.SelectedIndex - 1;
            //    h.message_size = message.Length;

            //    if (!WriteToChild(message, ref h))
            //    {
            //        MessageBox.Show("Внимание! Не удалось отправить сообщения!");
            //        return;
            //    }

            //    messageEvent.Set();
            //    confirmEvent.WaitOne();
            //}
            //else
            //{
            //    MessageBox.Show("Ошибка! Дочерняя программа не запущена!");
            //}
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            //closeProgrammEvent.Set();
            //if(child_process != null)
            //    child_process.Close();
        }

    }
}
