﻿/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt Charts入门与提高》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief 示例实现文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/
#include <QComboBox>
#include <qglobal.h>
#include <QRadioButton>
#include <QCheckBox>
#include <QGridLayout>
#include <QGraphicsItem>

#include "customchart.h"
#include "chartview.h"
#include "dialog.h"

const int maxSize1 = 100;
CDialog::CDialog(QWidget* pParent) : QDialog(pParent),
m_series1(NULL),
m_series2(NULL)
{
    setupUi(this);

    initialize();
}

CDialog::~CDialog()
{
	m_chart->removeAllSeries();
}
void CDialog::initialize()
{
	// 构建图表
    m_chart = new CCustomChart;			
	m_chart->setTitle("Custom Chart");

	m_pChartView = new CChartView(m_chart, widget);
	m_pChartView->setObjectName(QStringLiteral("m_pChartView"));
	gridLayout_7->addWidget(m_pChartView, 0, 0, 1, 1, Qt::AlignTop| Qt::AlignLeft);

	// 初始化各个配置参数控件
	initializeControls();

	m_tmLast = 0;

	// 构建系列1
	m_series1 = new QSplineSeries;	
	m_series1->setName("series_1");
	m_chart->addSeries(m_series1);	// 添加系列
	for(int i=0;i<maxSize1;++i){
		m_series1->append(i, getData(((double)i) / maxSize1));
	}

	// 构建系列2
	m_series2 = new QSplineSeries;	
	m_series2->setName("series_2");
	m_chart->addSeries(m_series2);	// 添加系列
	for (int i = 0; i<maxSize1; ++i) {
		m_series2->append(i, getData(((double)i+30) / maxSize1));
	}


	// 构建X坐标
	m_axisX = new QValueAxis;
	m_axisX->setRange(0, maxSize1);	// 设置坐标范围
	m_axisX->setLabelFormat("%g");	// 设置坐标文本的格式
	m_axisX->setTickCount(5);		// 刻度数
	m_axisX->setGridLineVisible(false);

 	// 构建Y坐标
	m_axisY = new QValueAxis;
    m_axisY->setRange(-10, 10);		// 设置坐标范围
    m_axisY->setTitleText("axisY");	// 设置坐标的标题
	m_chart->setAxisX(m_axisX, m_series1); // 为图表设置X坐标,并将坐标与系列1建立关联
	m_chart->setAxisX(m_axisX, m_series2); // 为图表设置X坐标,并将坐标与系列2建立关联
	m_chart->setAxisY(m_axisY, m_series1); // 为图表设置Y坐标,并将坐标与系列1建立关联
	m_chart->setAxisY(m_axisY, m_series2); // 为图表设置Y坐标,并将坐标与系列2建立关联
	m_axisY->setGridLineVisible(false);

    m_chart->setTheme(QChart::ChartThemeDark); // 设置主题
	m_pChartView->setChart(m_chart);		// 将图表绑定到视图

    m_chart->legend()->hide();				// 隐藏图例

	connectSignalSlots();

	updateUI();

}

void CDialog::initializeControls() {
	populateThemeBox();
	populateAnimationBox();
	populateLegendBox();

	QStringList strLst;
	strLst << "8" << "12" << "16" << "20";
	// 标题-字号
	cbFontSize_Title->insertItems(0, strLst);
	// 将下拉列表当前展示的字号设置为最后一个字号，也就是20号。
	cbFontSize_Title->setCurrentIndex(cbFontSize_Title->count() - 1);

	// X轴坐标-字号
	cbLabelFontSize_axisX->insertItems(0, strLst);
	// Y轴坐标-字号
	cbLabelFontSize_axisY->insertItems(0, strLst);

	// 标题-颜色
	strLst.clear();
	cbBrush_Title->addItem("red", (int)Qt::red);
	cbBrush_Title->addItem("green", (int)Qt::green);
	cbBrush_Title->addItem("black", (int)Qt::black);

	cbPenColor_Serie1->addItem("red", (int)Qt::red);
	cbPenColor_Serie1->addItem("green", (int)Qt::green);
	cbPenColor_Serie1->addItem("black", (int)Qt::black);

	cbPenColor_Serie2->addItem("red", (int)Qt::red);
	cbPenColor_Serie2->addItem("green", (int)Qt::green);
	cbPenColor_Serie2->addItem("black", (int)Qt::black);
	cbPenColor_Serie2->setCurrentIndex(1);

	antialiasCheckBox->setChecked(true);

	// add items to theme combobox
	cbZoom->addItem("NoRubberBand", QChartView::NoRubberBand);
	cbZoom->addItem("VerticalRubberBand", QChartView::VerticalRubberBand);
	cbZoom->addItem("HorizontalRubberBand", QChartView::HorizontalRubberBand);
	cbZoom->addItem("RectangleRubberBand", QChartView::RectangleRubberBand);

}

void CDialog::connectSignalSlots() {
	// 主题
	connect(themeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
	// 动画
	connect(animatedComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
	// 图例
	connect(legendComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
	// 反走样
	connect(antialiasCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
	
	// 标题-字体
	connect(ckLegendInPlotArea, SIGNAL(clicked()), this, SLOT(updateUI()));

	// 标题-字体
	connect(fontComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
	// 标题-字号
	connect(cbFontSize_Title, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
	// 标题-画刷
	connect(cbBrush_Title, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
	
	// 图表-画刷1
	connect(rbChartBrush_1, SIGNAL(clicked()), this, SLOT(updateUI()));
	// 图表-画刷2
	connect(rbChartBrush_2, SIGNAL(clicked()), this, SLOT(updateUI()));
	
	// 曲线区域-画刷1
	connect(rbPlotAreaBrush_1, SIGNAL(clicked()), this, SLOT(updateUI()));
	// 曲线区域-画刷2
	connect(rbPlotAreaBrush_2, SIGNAL(clicked()), this, SLOT(updateUI()));
	
	// X轴-title
    connect(leTextX, &QLineEdit::editingFinished, this, &CDialog::on_leTextX_editingFinished);
	// X轴-是否显示网格
	connect(cbGridLineVisibleX, SIGNAL(clicked()), this, SLOT(updateUI()));
	// X轴-坐标文本的字号
	connect(cbLabelFontSize_axisX, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
	// Y轴-title
    connect(leTextY, &QLineEdit::editingFinished, this, &CDialog::on_leTextY_editingFinished);
	// Y轴-是否显示网格
	connect(cbGridLineVisibleY, SIGNAL(clicked()), this, SLOT(updateUI()));
	// Y轴-坐标文本的字号
	connect(cbLabelFontSize_axisY, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));

	// 系列1-线色
  	connect(cbPenColor_Serie1, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
	// 系列1-线宽
  	connect(sbPenWidth_Serie1, SIGNAL(valueChanged(int)), this, SLOT(updateUI()));
	// 系列2-线色
  	connect(cbPenColor_Serie2, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
	// 系列2-线宽
  	connect(sbPenWidth_Serie2, SIGNAL(valueChanged(int)), this, SLOT(updateUI()));
	
	//connect(&m_timer, &QTimer::timeout, this, &CDialog::onTimeout);
 //	m_timer.setInterval(100);  // 100毫秒
	//m_timer.start();
	connect(m_series1, &QSplineSeries::hovered, this, &CDialog::serie1Hovered);
	connect(m_series2, &QSplineSeries::hovered, this, &CDialog::serie2Hovered);

	connect(m_series1, &QSplineSeries::pressed, this, &CDialog::serie1Pressed);
	connect(m_series2, &QSplineSeries::pressed, this, &CDialog::serie2Pressed);
	connect(m_series1, &QSplineSeries::pressed, m_chart, &CCustomChart::clickOnPoint);
	connect(m_series2, &QSplineSeries::pressed, m_chart, &CCustomChart::clickOnPoint);

	if (false) // 人工调整曲线时，暂时禁用tip功能
	{
		connect(m_series1, &QSplineSeries::clicked, m_pChartView, &CChartView::keepTip);
		connect(m_series1, &QSplineSeries::hovered, m_pChartView, &CChartView::tooltip);

		connect(m_series2, &QSplineSeries::clicked, m_pChartView, &CChartView::keepTip);
		connect(m_series2, &QSplineSeries::hovered, m_pChartView, &CChartView::tooltip);

	}

	connectMarkers();
	// zoom
  	//connect(cbZoom, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
	connect(cbZoom, &QComboBox::currentTextChanged, this, &CDialog::updateUI);

}

void CDialog::serie1Pressed(const QPointF& /*pt*/)
{
	m_chart->setSelectedSerie(m_series1);
}

void CDialog::serie2Pressed(const QPointF& /*pt*/)
{
	m_chart->setSelectedSerie(m_series2);
}

void CDialog::serie1Hovered(const QPointF& /*pt*/, bool bState)
{
	QPen penHighLight(Qt::white, 5);
	if (bState) {
		m_series1->setPen(penHighLight);
	}
	else {
		QVariant varColor = cbPenColor_Serie1->itemData(cbPenColor_Serie1->currentIndex());
		Qt::GlobalColor clr = static_cast<Qt::GlobalColor>(varColor.toInt());
		QPen pn2(clr, sbPenWidth_Serie1->value());
		m_series1->setPen(pn2);
	}
}

void CDialog::serie2Hovered(const QPointF& /*pt*/, bool bState)
{
	QPen penHighLight(Qt::white, 5);
	if (bState) {
		m_series2->setPen(penHighLight);
	}
	else{
		Qt::GlobalColor clr = static_cast<Qt::GlobalColor>(cbPenColor_Serie2->itemData(cbPenColor_Serie2->currentIndex()).toInt());
		QPen pn2(clr, sbPenWidth_Serie2->value());
		m_series2->setPen(pn2);
	}
}
void CDialog::setDialogPalette() {
	QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(
		themeComboBox->itemData(themeComboBox->currentIndex()).toInt());

	// Set palette colors based on selected theme
	QPalette pal = window()->palette();
	if (theme == QChart::ChartThemeLight) {
		pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
		pal.setColor(QPalette::WindowText, QRgb(0x404044));
	}
	else if (theme == QChart::ChartThemeDark) {
		pal.setColor(QPalette::Window, QRgb(0x121218));
		pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
	}
	else if (theme == QChart::ChartThemeBlueCerulean) {
		pal.setColor(QPalette::Window, QRgb(0x40434a));
		pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
	}
	else if (theme == QChart::ChartThemeBrownSand) {
		pal.setColor(QPalette::Window, QRgb(0x9e8965));
		pal.setColor(QPalette::WindowText, QRgb(0x404044));
	}
	else if (theme == QChart::ChartThemeBlueNcs) {
		pal.setColor(QPalette::Window, QRgb(0x018bba));
		pal.setColor(QPalette::WindowText, QRgb(0x404044));
	}
	else if (theme == QChart::ChartThemeHighContrast) {
		pal.setColor(QPalette::Window, QRgb(0xffab03));
		pal.setColor(QPalette::WindowText, QRgb(0x181818));
	}
	else if (theme == QChart::ChartThemeBlueIcy) {
		pal.setColor(QPalette::Window, QRgb(0xcee7f0));
		pal.setColor(QPalette::WindowText, QRgb(0x404044));
	}
	else {
		pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
		pal.setColor(QPalette::WindowText, QRgb(0x404044));
	}
	window()->setPalette(pal);
}


void CDialog::updateUI()
{
	// 设置主题
	QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(
		themeComboBox->itemData(themeComboBox->currentIndex()).toInt());
	m_chart->setTheme(theme);

	// 根据主题设置整个窗体的调色板
	setDialogPalette();
	

	// Update antialiasing
	bool checked = antialiasCheckBox->isChecked();
	m_pChartView->setRenderHint(QPainter::Antialiasing, checked);

	// Update animation options
	QChart::AnimationOptions options(
		animatedComboBox->itemData(animatedComboBox->currentIndex()).toInt());
	if (m_chart->animationOptions() != options) {
		m_chart->setAnimationOptions(options);
	}

	// Update legend alignment
	Qt::Alignment alignment(legendComboBox->itemData(legendComboBox->currentIndex()).toInt());

	QLegend *legend = m_chart->legend();
	if (!alignment) {
		if (ckLegendInPlotArea->isChecked()) {
			if (legend->isAttachedToChart()) {
				legend->detachFromChart();
				legend->setBackgroundVisible(true);
				legend->setBrush(QBrush(QColor(128, 128, 128, 128)));
				legend->setPen(QPen(QColor(192, 192, 192, 192)));
				legend->setGeometry(m_chart->geometry().center().x()+100, 0, 100, 60);
			}
			legend->show();
			legend->setFlags(QGraphicsItem::GraphicsItemFlags(QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable));
		}
		else {
			legend->hide();
		}
	}
	else {
		legend->attachToChart();
		//legend->detachFromChart();

		legend->setBackgroundVisible(false);
		legend->setAlignment(alignment);
		legend->show();
	}
	legend->update();
	update();

	QString strFamily = fontComboBox->currentText();
	QFont font;
	font.setPixelSize(cbFontSize_Title->currentText().toInt());
	font.setFamily(strFamily);
	m_chart->setTitleFont(font);


	// chart brush
	if (rbChartBrush_1->isChecked()) {
		m_chart->setBackgroundBrush(Qt::gray);
	}
	else {
		m_chart->setBackgroundBrush(Qt::yellow);
	}

	// plotarea brush
	m_chart->setPlotAreaBackgroundVisible(true);
	if (rbPlotAreaBrush_1->isChecked()) {
		m_chart->setPlotAreaBackgroundBrush(Qt::darkBlue);
	}
	else {
		m_chart->setPlotAreaBackgroundBrush(Qt::darkMagenta);
	}

	// 是否显示刻度线
	m_axisX->setGridLineVisible(cbGridLineVisibleX->isChecked());
	m_axisY->setGridLineVisible(cbGridLineVisibleY->isChecked());

	// 设置坐标轴字体 
	QFont labelsFont;
	labelsFont.setPixelSize(cbLabelFontSize_axisX->currentText().toInt()); 
	m_axisX->setLabelsFont(labelsFont); // X轴
	labelsFont.setPixelSize(cbLabelFontSize_axisY->currentText().toInt());
	m_axisY->setLabelsFont(labelsFont);	// Y轴

	// 主题-字体颜色
	Qt::GlobalColor clr = static_cast<Qt::GlobalColor>(cbBrush_Title->itemData(cbBrush_Title->currentIndex()).toInt());
	m_chart->setTitleBrush(clr);
	
	// 设置系列1的线色
	clr = static_cast<Qt::GlobalColor>(cbPenColor_Serie1->itemData(cbPenColor_Serie1->currentIndex()).toInt());
	QPen pn1(clr, sbPenWidth_Serie1->value());
	m_series1->setPen(pn1);

	// 设置系列2的线色
	clr = static_cast<Qt::GlobalColor>(cbPenColor_Serie2->itemData(cbPenColor_Serie2->currentIndex()).toInt());
	QPen pn2(clr, sbPenWidth_Serie2->value());
	m_series2->setPen(pn2);

	int nVal = cbZoom->itemData(cbZoom->currentIndex()).toInt();
	QChartView::RubberBand rubberBand = static_cast<QChartView::RubberBand>(nVal);
	m_pChartView->setRubberBand(rubberBand);
	if (QChartView::NoRubberBand == rubberBand) {
		m_chart->zoomReset();
	}

}

void CDialog::on_leTextX_editingFinished()
{
    QString str = leTextX->text();
    m_axisX->setTitleText(str);
}

void CDialog::on_leTextY_editingFinished()
{
    QString str = leTextY->text();
    m_axisY->setTitleText(str);
}

double CDialog::getData(double time)
{
    double s = qSin( time * M_PI * 2 )*7 ;
    return s;
}
void CDialog::resizeEvent(QResizeEvent *event)
{
	QDialog::resizeEvent(event);
	m_pChartView->setSize(widget->size());
}
void CDialog::onTimeout()
{
	static QTime tmBegin(QTime::currentTime());
	long int tmElapsed = tmBegin.elapsed();
	int nSkip = (tmElapsed - m_tmLast);// 数据个数
	qDebug() << "skip data count:" << nSkip;
	if (isVisible()) {
		QVector<QPointF> ptsOld = m_series1->pointsVector();
		QVector<QPointF> ptsNew;

		// 跳过一些数据。两次定时之间流失的时间作为跳过的数据个数。
		for (int i = nSkip; i<ptsOld.count(); ++i) {
			// 新数据的第0个坐标，存放的是 ptsOld 的第nSkip坐标处的数据。
			ptsNew.append(QPointF(i - nSkip, ptsOld.at(i).y()));// 跳过nSkip个数据
		}

		// 补充新数据：从跳过后的数据点开始，获取新数据。
		qint64 sizePoints = ptsOld.count() - nSkip;
		for (int k = 0; k<nSkip; ++k) {
			// 追加的第一个坐标：0+sizePoints=旧数据个数-跳过的个数=剩余数据起始点坐标
			ptsNew.append(QPointF(k + sizePoints, getData((((double)m_tmLast + k + 1) / maxSize1))));
		}
		m_series1->replace(ptsNew);
		m_tmLast = tmElapsed;
	}
}


void CDialog::populateThemeBox()
{
	// add items to theme combobox
	themeComboBox->addItem("Light", QChart::ChartThemeLight);
	themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
	themeComboBox->addItem("Dark", QChart::ChartThemeDark);
	themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
	themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
	themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
	themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
	themeComboBox->addItem("Qt", QChart::ChartThemeQt);
}

void CDialog::populateAnimationBox()
{
	// add items to animation combobox
	animatedComboBox->addItem("No Animations", QChart::NoAnimation);
	animatedComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
	animatedComboBox->addItem("Series Animations", QChart::SeriesAnimations);
	animatedComboBox->addItem("All Animations", QChart::AllAnimations);
}

void CDialog::populateLegendBox()
{
	// add items to legend combobox
	legendComboBox->addItem("No Legend ", 0);
	legendComboBox->addItem("Legend Top", Qt::AlignTop);
	legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
	legendComboBox->addItem("Legend Left", Qt::AlignLeft);
	legendComboBox->addItem("Legend Right", Qt::AlignRight);
}


void CDialog::connectMarkers()
{
	// Connect all markers to handler
	const auto markers = m_chart->legend()->markers();
	for (QLegendMarker *marker : markers) {
		// 断开已有信号槽的连接，防止重复连接。
		QObject::disconnect(marker, &QLegendMarker::clicked,
			this, &CDialog::handleMarkerClicked);
		QObject::connect(marker, &QLegendMarker::clicked, this, &CDialog::handleMarkerClicked);
	}
}

void CDialog::disconnectMarkers()
{
	const auto markers = m_chart->legend()->markers();
	for (QLegendMarker *marker : markers) {
		QObject::disconnect(marker, &QLegendMarker::clicked,
			this, &CDialog::handleMarkerClicked);
	}
}

void CDialog::handleMarkerClicked()
{
	QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
	Q_ASSERT(marker);

	switch (marker->type())
	{
	case QLegendMarker::LegendMarkerTypeXY:
	{
		
		// Toggle visibility of series
		marker->series()->setVisible(!marker->series()->isVisible());

		// Turn legend marker back to visible, since hiding series also hides the marker
		// and we don't want it to happen now.
		marker->setVisible(true);

		// Dim the marker, if series is not visible
		qreal alpha = 1.0;

		if (!marker->series()->isVisible())
			alpha = 0.5;

		QColor color;
		QBrush brush = marker->labelBrush();
		color = brush.color();
		color.setAlphaF(alpha);
		brush.setColor(color);
		marker->setLabelBrush(brush);

		brush = marker->brush();
		color = brush.color();
		color.setAlphaF(alpha);
		brush.setColor(color);
		marker->setBrush(brush);

		QPen pen = marker->pen();
		color = pen.color();
		color.setAlphaF(alpha);
		pen.setColor(color);
		marker->setPen(pen);
		break;
	}
	default:
	{
		qDebug() << "Unknown marker type";
		break;
	}
	}
}
