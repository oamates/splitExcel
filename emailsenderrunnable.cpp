#include "emailsenderrunnable.h"

EmailSenderRunnable::EmailSenderRunnable(QObject *parent)
{
    this->mParent = parent;
}

EmailSenderRunnable::~EmailSenderRunnable()
{
    runnableID = 0;
}

void EmailSenderRunnable::setID(const int &id)
{
    runnableID = id;
}

void EmailSenderRunnable::setSendData(QString userName,QString password, QString server,QString defaultSender,QString savePath,QString key,QList<QStringList> content)
{
    qDebug("setSendData") ;
    this->userName = userName;
    this->password = password;
    this->server = server;
    this->defaultSender = defaultSender;
    this->savePath = savePath;
    this->key = key;
    this->content = content;
}

void EmailSenderRunnable::run()
{
    qDebug("EmailSenderRunnable::run start") ;
    requestMsg(Common::MsgTypeInfo, "准备发送邮件。。。" + key);
    SmtpClient *smtpClient = new SmtpClient(server);
    smtpClient->setUser(userName);
    smtpClient->setPassword(password);

    if(!smtpClient->connectToHost())
    {
        requestMsg(Common::MsgTypeError, "邮件服务器连接失败！！");
        return;
    }

    if (!smtpClient->login(userName, password))
    {
        requestMsg(Common::MsgTypeError, "邮件服务器认证失败（邮件用户名或者密码错误）!!");
        return;
    }
    requestMsg(Common::MsgTypeInfo, "开始发送邮件。。。"+key);

    MimeMessage mineMsg;

    //防止中文乱码
    mineMsg.setHeaderEncoding(MimePart::Encoding::Base64);
    mineMsg.setSender(new EmailAddress(defaultSender, defaultSender));

    QString attementsName;
    attementsName.append(savePath).append("\\").append(key).append(".xlsx");

    // Add an another attachment
    QFileInfo file(attementsName);
    if (file.exists())
    {
        MimeAttachment *attachment = new MimeAttachment(new QFile(attementsName));
        attachment->setEncoding(MimePart::Encoding::Base64);
        attachment->setContentName("attachment.xlsx");
        mineMsg.addPart(attachment);
    }
    else
    {
        qDebug("file not exists:") ;
        qDebug(attementsName.toUtf8());
    }

    //只取一行数据
    QStringList emailData = content.at(0);

    if (emailData.size() < 4)
    {
        requestMsg(Common::MsgTypeError, "Email sheet 数据错误。数据列必须为4行 分别为 站，email地址，email标题，email内容");
        return;
    }
    //email的数据顺序为  （站，email,title,content）
    EmailAddress * email = new EmailAddress(emailData.at(1), emailData.at(1));
    mineMsg.addRecipient(email);
    mineMsg.setSubject(emailData.at(2));

    MimeText text;
    text.setText(emailData.at(3));
    mineMsg.addPart(&text);

    if (smtpClient->sendMail(mineMsg))
    {//success
        requestMsg(Common::MsgTypeSucc,"邮件发送成功。。。" + key);
    }
    else
    {//failure
        requestMsg(Common::MsgTypeFail,"邮件发送失败。。。" + key);
    }
    smtpClient->quit();
    qDebug("EmailSenderRunnable::run end") ;
}
void EmailSenderRunnable::requestMsg(const int msgType, const QString &msg)
{
    QMetaObject::invokeMethod(mParent, "receiveMessage", Qt::QueuedConnection, Q_ARG(int,msgType),Q_ARG(QString, msg));
}
