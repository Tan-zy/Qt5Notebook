﻿/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt Charts入门与提高》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.h
\brief 示例头文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/
#ifndef DIALOG_H
#define DIALOG_H

#include <QtCharts>		// xingdianketang
QT_CHARTS_USE_NAMESPACE// xingdianketang

QT_CHARTS_BEGIN_NAMESPACE
class QCategoryAxis;
QT_CHARTS_END_NAMESPACE

class CChartView;
class CCustomChart;
class CDrillDownChart;
class CTableModel;

#include "ui_dialogbase.h" // 头文件名称来自: dialogbase.ui  ---> ui_dialogbase.h

// 第一个父类的名称来自ui文件中对话框的类名：对象查看器中的类名
// 第二个父类的名称来自ui文件中对话框基类的名称(objeceName属性)： CDialogBase
class CDialog : public QDialog, public Ui::CDialogBase
{
	Q_OBJECT
public:
	CDialog(QWidget* pParent);
	~CDialog();
private slots:
	void onTimeout();

    void on_leTextX_editingFinished();
	;
    void on_leTextY_editingFinished();
	void updateUI();
	void serie1Hovered(const QPointF&,bool);
	void serie2Hovered(const QPointF&,bool);
	void serie1Pressed(const QPointF&);
	void serie2Pressed(const QPointF&);
	void connectMarkers();
	void disconnectMarkers();
	void handleMarkerClicked();
	void addBarset();
	void removeBarset();
	void tabChanged();

protected:
	void resizeEvent(QResizeEvent *event);
private:
	/**
	* @brief 初始化。
	*/
	void initialize();
	/**
	* @brief 初始化曲线。
	*/
	void initializeCurveSeries();
	/**
	* @brief 初始化棒图。
	*/
	void initializeBarSeries();

	/**
	* @brief 初始化饼图。
	*/
	void initializePieSeries();
	/**
	* @brief 初始化雷达图。
	*/
	void initializePolar();
	/**
	* @brief 获取曲线数据。
	* @param[in] time 时间点。
	* @return 对应的曲线数据
	*/
    double getData(double time);
	/**
	* @brief 初始化主题。
	* @return void
	*/
	void populateThemeBox();
	/**
	* @brief 初始化主题动画选项。
	* @return void
	*/
	void populateAnimationBox();
	/**
	* @brief 初始化图例选项。
	* @return void
	*/
	void populateLegendBox();
	/**
	* @brief 绑定信号槽。
	* @return void
	*/
	void connectSignalSlots();
	/**
	* @brief 根据主题设置整个对话框窗体的调色板。
	* @return void
	*/
	void setDialogPalette();

	/**
	* @brief 初始化各个配置参数控件。
	* @return void
	*/
	void initializeControls();
	/**
	* @brief 复位饼图图表。即重新显示饼图图表。
	* @return void
	*/
	void resetPieChart();

private:
	QSplineSeries *m_series1;
	QSplineSeries *m_series2;
	QBarSeries	  *m_seriesBar;
	QPieSeries	  *m_seriesPie;
	QChart		  *m_barChart;
	QChart		  *m_chart;
	QPolarChart	  *m_polarChart;
	CDrillDownChart *m_pieChart;
	CCustomChart  *m_curveChart;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
	QCategoryAxis *m_axisY3;
	QTimer		m_timer;
	int			m_tmLast;
	QChartView  *m_pChartView;
	QChartView  *m_pBarChartView;
	CChartView  *m_pCurveChartView;
	QChartView  *m_pPieChartView;
	QChartView  *m_pPolarChartView;
	QTableView* m_curveTableView;
	QTableView* m_barTableView;
	CTableModel *m_curveModel;
	CTableModel *m_barModel;
	QVBarModelMapper *m_barModelMapper;
	QBarSet *set0;
	QBarSet *set1;
	QBarSet *set2;
	QBarSet *set3;
	QBarSet *set4;

};

#endif
