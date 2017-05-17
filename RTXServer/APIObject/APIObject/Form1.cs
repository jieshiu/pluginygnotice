using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using RTXSAPILib;
using System.Runtime.InteropServices;
using System.IO;
using System.Net;

namespace APIObject
{
    public partial class Form1 : Form
    {
        RTXSAPILib.RTXSAPIRootObj RootObj;  //声明一个根对象
        RTXSAPILib.RTXSAPIObj ApiObj;       //声明一个应用对象
        RTXSAPILib.RTXSAPIMessage MsgObj;   //声明一个消息对象
        RTXSAPILib.RTXSData DataObj;        //声明一个SData对象

        public delegate void AddText(RTXSAPILib.RTXSAPIMessage strMessage);
        public AddText mydelegate;
        HttpWebResponse Response = null;
        public Form1()
        {
            InitializeComponent();

            RootObj = new RTXSAPIRootObj();     //创建根对象
            ApiObj = RootObj.CreateAPIObj();    //通过根对象创建应用对象
            MsgObj = ApiObj.CreateMessage();    //通过应用对象创建消息对象
            DataObj = RootObj.CreateRTXSData(); //通过根对象创建SData对象

            ApiObj.OnRecvMessage +=new _IRTXSAPIObjEvents_OnRecvMessageEventHandler(ApiObj_OnRecvMessage); //订阅一个事件，当收到客户端插件发过来的消息时触发该事件

            mydelegate = new AddText(AddTextMethod);
        }

        public void AddTextMethod(RTXSAPILib.RTXSAPIMessage strMessage)
        {
            txtResult.Text = strMessage.Sender + "发送:" + strMessage.Content + "到:" + strMessage.Receivers;
            txtReceiver.Text = strMessage.Sender;

        }
        
        private void SendNoticeData(string csSendData, string csReceiver)
        {

            RTXSAPILib.RTXSData sendData = RootObj.CreateRTXSData(); // 创建一个SData对象

            //封装协议包，可理解SDataObj是一个协议包，该协议包被封装进消息对象MsgObj，然后调用应用对象的SendMessage方法把MsgObj发送给客户端
            sendData.SetString("Sender", "{16F8F6DB-EB21-4520-8371-421DD76A9149}");  // 设置发送者
            sendData.SetString("Content", csSendData);   // 设置消息内容
            //为了容易理解，本示例协议包只有两个字段，这些字段名称可以自行名称。

            MsgObj.Sender = "{16F8F6DB-EB21-4520-8371-421DD76A9149}";//'设置发送者，该GUID为应用的GUID。
            MsgObj.Receivers = csReceiver;  //设置接收者
            MsgObj.MsgType = "Tencent.RTX.PlugInYgNotice"; //设置消息类型，该消息类型可以在客户端插件查看
            MsgObj.AppName = "Tencent.RTX.PlugInYgNotice";  //该名为客户端插件的名称，插件名称一般与消息类型一致
            MsgObj.Content = sendData.XML; // 把SData导出为xml格式后赋值给Content
            MsgObj.MessageFlag = RTXSAPI_MESSAGE_FLAG.RTXSAPI_MESSAGE_FLAG_DEFAULT; //默认的处理方式，允许其它应用过滤消息，也允许以抽取的方式对消息进行过滤

            try
            {
                ApiObj.SendMessage(MsgObj, false); //把MsgObj发给客户端

            }
            catch (COMException xe)
            {
                //MessageBox.Show(xe.Message);
            }

        }

        private void ApiObj_OnRecvMessage(RTXSAPILib.RTXSAPIMessage Message) //接收到插件发来的消息触发该事件
        {
            try
            {
                txtResult.BeginInvoke(mydelegate, Message); //把信息显示到文本框


                //拆开协议包，把Message.Content赋值给一个SData对象，通过SData对象的方法获取里面字段的值
                RTXSAPILib.RTXSData ReceiverData; //声明一个SData对象     
                ReceiverData = RootObj.CreateRTXSData();  //创建它
                ReceiverData.XML = Message.Content;// 把Message.Content赋值给ReceiverData.XML
                string csSend=ReceiverData.GetString("Sender");
                string csReceiver = ReceiverData.GetString("Receiver");
                string csSendTime = ReceiverData.GetString("SendTime");
                string csType = ReceiverData.GetString("Type");
                string csContent = ReceiverData.GetString("Content");

                if (csType == "NOTICE")
                {
                    string csSendNotice = "NOTICE|" + csReceiver + "|0|" + csContent;
                    SendNoticeData(csSendNotice, csReceiver);
                }
                else if(csType == "TALK")
                {                    
                    //string returnMess = ConnectTuLing(csContent); 
                    string returnMess = "敬请期待！";
                    string csSendTalk = "TALK|" + returnMess;
                    SendNoticeData(csSendTalk, csSend);
                }


            }
            catch (COMException xe)
            {
                MessageBox.Show(xe.Message);
            }

        }

        private void btnRegApp_Click(object sender, EventArgs e)
        {
            ApiObj.ServerIP = txtServerIP.Text;    //设置服务器IP,,必填参数
            ApiObj.ServerPort = Convert.ToInt16(txtServerPort.Text);    //设置服务器端口,,必填参数
            ApiObj.AppGUID = txtAppGuid.Text;      //设置应用GUID,,必填参数
            ApiObj.AppName = txtAppName.Text;      //设置应用名称,,必填参数


            if (txtFilterAction.Text == "distill")  
            {
                ApiObj.AppAction = RTXSAPI_APP_ACTION.AA_DISTILL;
            }
            else if (txtFilterAction.Text == "copy")        // 当过滤动作为AA_DISTILL时，ConServer把消息拷贝给应用后删除原来的消息。
            {
                ApiObj.AppAction = RTXSAPI_APP_ACTION.AA_COPY; //设置过滤动作,当过滤动作为AA_COPY时，ConServer把消息拷贝一份给应用，但不会删除原来的消息。
            }
            else
            {
                MessageBox.Show("输入有误，请重新输入");

            }



            ApiObj.FilterAppName = "All";   // 表示过滤所有应用,必填参数
            ApiObj.FilterRequestType = txtFilterRequestTy.Text ; // 过滤消息类型,必填参数
            ApiObj.FilterResponseType = "none"; // 无回复消息类型,必填参数
            ApiObj.FilterSender = "anyone";    //过滤所有发送人的该类消息,必填参数
            ApiObj.FilterReceiver = "anyone"; //过滤所有接收人的该类消息,必填参数
            ApiObj.FilterReceiverState = "anystate" ; // 关注所有状态,必填参数
            ApiObj.FilterKey = "";


            try
            {
                ApiObj.RegisterApp();   //注册应用
                MessageBox.Show("注册成功");

            }
            catch (COMException xe)
            {
                MessageBox.Show(xe.Message);
            }

        }



        private void btnStartApp_Click(object sender, EventArgs e)
        {
            try
            {
                ApiObj.StartApp("", 4);     //启动应用
                MessageBox.Show("启动成功");
            }
            catch (COMException xe)
            {
                MessageBox.Show(xe.Message);
            }

        }

        private void btnStopApp_Click(object sender, EventArgs e)
        {
            try
            {
                ApiObj.StopApp();   //停止应用
                MessageBox.Show("停止成功");
            }
            catch (COMException xe)
            {
                MessageBox.Show(xe.Message);
            }
        }

        private void btnUnregApp_Click(object sender, EventArgs e)
        {
            try
            {
                ApiObj.ServerIP = txtServerIP.Text;    //设置服务器IP,,必填参数
                ApiObj.ServerPort = Convert.ToInt16(txtServerPort.Text);    //设置服务器端口,,必填参数
                ApiObj.AppGUID = txtAppGuid.Text;      //设置应用GUID,,必填参数
                ApiObj.AppName = txtAppName.Text;      //设置应用名称,,必填参数
                ApiObj.UnRegisterApp();     //注销应用
                MessageBox.Show("注销成功");
            }
            catch (COMException xe)
            {
                MessageBox.Show(xe.Message);
            }
        }

        private void btnSendData_Click(object sender, EventArgs e)
        {

            RTXSAPILib.RTXSData sendData  = RootObj .CreateRTXSData (); // 创建一个SData对象

            //封装协议包，可理解SDataObj是一个协议包，该协议包被封装进消息对象MsgObj，然后调用应用对象的SendMessage方法把MsgObj发送给客户端
            sendData.SetString ("Sender", "{16F8F6DB-EB21-4520-8371-421DD76A9149}");  // 设置发送者
            sendData.SetString ("Content", txtContent .Text );   // 设置消息内容
            //为了容易理解，本示例协议包只有两个字段，这些字段名称可以自行名称。

            MsgObj.Sender = "{16F8F6DB-EB21-4520-8371-421DD76A9149}";//'设置发送者，该GUID为应用的GUID。
            MsgObj.Receivers = txtReceiver.Text;  //设置接收者
            MsgObj.MsgType = "Tencent.RTX.PlugInYgNotice"; //设置消息类型，该消息类型可以在客户端插件查看
            MsgObj.AppName = "Tencent.RTX.PlugInYgNotice";  //该名为客户端插件的名称，插件名称一般与消息类型一致
            MsgObj.Content = sendData.XML; // 把SData导出为xml格式后赋值给Content
            MsgObj.MessageFlag = RTXSAPI_MESSAGE_FLAG .RTXSAPI_MESSAGE_FLAG_DEFAULT ; //默认的处理方式，允许其它应用过滤消息，也允许以抽取的方式对消息进行过滤

            try
            {
                ApiObj .SendMessage (MsgObj,false ); //把MsgObj发给客户端

            }
            catch (COMException xe)
            {
                MessageBox.Show(xe.Message);
            }

        }

    }
}