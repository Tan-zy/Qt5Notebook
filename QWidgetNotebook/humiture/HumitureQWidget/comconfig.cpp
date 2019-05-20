#include "comconfig.h"
#include "ui_comconfig.h"

ComConfig::ComConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComConfig)
{
    ui->setupUi(this);
    // 自定义 ComboBox 的样式
    ui->comboBox_com->setView(new QListView);
    for(int i = 1; i < 16; i++){
        ui->comboBox_com->addItem(QString("COM%1").arg(i));
    }
    ui->comboBox_baud->setView(new QListView);
    QStringList bauds;
    bauds << "1200" << "2400" << "4800" << "9600" << "19200";
    ui->comboBox_baud->addItems(bauds);
}

ComConfig::~ComConfig()
{
    delete ui;
}

void ComConfig::on_pushButton_com_clicked()
{
    if(ui->pushButton_com->text() == "打开"){
        QString com = ui->comboBox_com->currentText();
        int baud = ui->comboBox_baud->currentText().toInt();
        Task task;
        task.m_page = 1;
        task.task_type = Task::TaskType::Open_Device;
        task.m_isRtu = true;
        task.rtuModbusInfo.m_baud = baud;
        task.rtuModbusInfo.m_comDevice = com;
        task.rtuModbusInfo.m_parity = "N";
        task.rtuModbusInfo.m_rsModel = MODBUS_RTU_RS485;
        task.rtuModbusInfo.m_databits = 8;
        task.rtuModbusInfo.m_stopbits = 1;
        QVariant msg;
        msg.setValue(task);
        emit openCom(msg);
    }else {
        Task task;
        task.m_page = 1;
        task.task_type = Task::TaskType::Close_Device;
        QVariant msg;
        msg.setValue(task);
        emit closeCom(msg);
    }
}

void ComConfig::onOpenResult(bool result, QVariant msg)
{
    if(result){
        Task value = msg.value<Task>();
        ui->pushButton_com->setText("关闭");
        ui->label_baud->setText(QString("%1").arg(value.rtuModbusInfo.m_baud));
        ui->label_stopbits->setText(QString("%1").arg(value.rtuModbusInfo.m_stopbits));
        ui->label_paritybits->setText(QString("%1").arg(value.rtuModbusInfo.m_parity));
        ui->label_databits->setText(QString("%1").arg(value.rtuModbusInfo.m_databits));
        ui->label_com_status->setText("串口状态: 已打开");
    }else{
        ui->label_com_status->setText("串口状态: 打开失败");
    }
}
void ComConfig::onExitResult()
{
    ui->pushButton_com->setText("打开");
    ui->label_baud->setText("");
    ui->label_stopbits->setText("");
    ui->label_paritybits->setText("");
    ui->label_databits->setText("");
    ui->label_com_status->setText("串口状态:");
}