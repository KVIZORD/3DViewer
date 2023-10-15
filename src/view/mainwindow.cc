#include "include/mainwindow.h"


#include "ui_mainwindow.h"


namespace s21 {

MainWindow::MainWindow(Facade& ctrl, QWidget *parent) : QMainWindow(parent), controller(ctrl), ui(new Ui::MainWindow), scene_params(ctrl.GetSettings()) {
    ui->setupUi(this);

    InitSettings();
    controller.SetParentForSceneDraw(ui->widgetOpenGL);
    controller.SetParamsScene(&scene_params);
    ui->screenPath->setText(screen_dir);
    ui->screenPath->setToolTip(screen_dir);
    ui->gifPath->setText(gif_dir);
    ui->gifPath->setToolTip(gif_dir);

    connect(ui->buttonSelectFile, SIGNAL(clicked()), this, SLOT(SlotSelectFile()));
    connect(ui->buttonRenderObj,  SIGNAL(clicked()), this, SLOT(SlotRenderScene()));

    connect(ui->typeProjection,  SIGNAL(activated(int)),    this, SLOT(SlotChangeTypeProjection(int)));
    connect(ui->backgroundColor, SIGNAL(clicked()),         this, SLOT(SlotChangeBackground()));
    connect(ui->lineType,        SIGNAL(activated(int)),    this, SLOT(SlotChangeEdgeType(int)));
    connect(ui->lineWidth,       SIGNAL(valueChanged(int)), this, SLOT(SlotChangeEdgeWidth(int)));
    connect(ui->lineColor,       SIGNAL(clicked()),         this, SLOT(SlotChangeEdgeColor()));
    connect(ui->vertexType,      SIGNAL(activated(int)),    this, SLOT(SlotChangeVertexType(int)));
    connect(ui->vertexSize,      SIGNAL(valueChanged(int)), this, SLOT(SlotChangeVertexSize(int)));
    connect(ui->vertexColor,     SIGNAL(clicked()),         this, SLOT(SlotChangeVertexColor()));

    connect(ui->moveX,          SIGNAL(valueChanged(int)), this, SLOT(SlotMoveObjectX(int)));
    connect(ui->moveY,          SIGNAL(valueChanged(int)), this, SLOT(SlotMoveObjectY(int)));
    connect(ui->moveZ,          SIGNAL(valueChanged(int)), this, SLOT(SlotMoveObjectZ(int)));
    connect(ui->sliderMoveX,    SIGNAL(valueChanged(int)), this, SLOT(SlotMoveObjectX(int)));
    connect(ui->sliderMoveY,    SIGNAL(valueChanged(int)), this, SLOT(SlotMoveObjectY(int)));
    connect(ui->sliderMoveZ,    SIGNAL(valueChanged(int)), this, SLOT(SlotMoveObjectZ(int)));

    connect(ui->rotateX,        SIGNAL(valueChanged(int)), this, SLOT(SlotRotateObjectX(int)));
    connect(ui->rotateY,        SIGNAL(valueChanged(int)), this, SLOT(SlotRotateObjectY(int)));
    connect(ui->rotateZ,        SIGNAL(valueChanged(int)), this, SLOT(SlotRotateObjectZ(int)));
    connect(ui->sliderRotateX,  SIGNAL(valueChanged(int)), this, SLOT(SlotRotateObjectX(int)));
    connect(ui->sliderRotateY,  SIGNAL(valueChanged(int)), this, SLOT(SlotRotateObjectY(int)));
    connect(ui->sliderRotateZ,  SIGNAL(valueChanged(int)), this, SLOT(SlotRotateObjectZ(int)));

    connect(ui->scale,          SIGNAL(valueChanged(int)), this, SLOT(SlotScaleObjectXYZ(int)));
    connect(ui->sliderScale,    SIGNAL(valueChanged(int)), this, SLOT(SlotScaleObjectXYZ(int)));

    connect(ui->screenPath,             SIGNAL(clicked()), this, SLOT(SlotSelectScreenPath()));
    connect(ui->buttonPreentScreenBmp,  SIGNAL(clicked()), this, SLOT(SlotPrintScreenBMP()));
    connect(ui->buttonPreentScreenJpeg, SIGNAL(clicked()), this, SLOT(SlotPrintScreenJPEG()));

    connect(ui->gifPath,         SIGNAL(clicked()), this, SLOT(SlotSelectGifPath()));
    connect(ui->buttonCreateGif, SIGNAL(clicked()), this, SLOT(SlotMakeGif()));
}

MainWindow::~MainWindow() {
    controller.SetParentForSceneDraw(nullptr);
    delete ui;
}

void MainWindow::InitSettings() {
    ui->typeProjection->setCurrentIndex(scene_params.type_projection);
    ui->lineType->setCurrentIndex(static_cast<int>(scene_params.edge_type));
    ui->vertexType->setCurrentIndex(static_cast<int>(scene_params.vertex_type));
    ui->lineWidth->setValue(scene_params.edge_width);
    ui->vertexSize->setValue(scene_params.vertex_size);
    ui->lineColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)").arg(scene_params.edge_color.red()).arg(scene_params.edge_color.green()).arg(scene_params.edge_color.blue()));
    ui->backgroundColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)").arg(scene_params.background_color.red()).arg(scene_params.background_color.green()).arg(scene_params.background_color.blue()));
    ui->vertexColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)").arg(scene_params.vertex_color.red()).arg(scene_params.vertex_color.green()).arg(scene_params.vertex_color.blue()));
}


void MainWindow::Notify() {
    controller.UpdateScene();
    controller.UpdateSettings(scene_params);
}

void MainWindow::SlotSelectFile() {
    file_path = QFileDialog::getOpenFileName(this, "Open File", "./", tr("*.obj"));
    QFileInfo fileinfo(file_path);
    ui->fileName->setText(fileinfo.fileName());
}

void MainWindow::SlotRenderScene() {
    controller.LoadScene(file_path);

}

void MainWindow::SlotMoveObjectX(int offset) {
    if (offset == previous_offsets.x) {
        return;
    }
    controller.MoveScene(offset - previous_offsets.x, 0, 0);
    previous_offsets.x = offset;
    ui->sliderMoveX->setSliderPosition(offset);
    ui->moveX->setValue(offset);
}

void MainWindow::SlotMoveObjectY(int offset) {
    if (offset == previous_offsets.y) {
        return;
    }
    controller.MoveScene(0, offset - previous_offsets.y, 0);
    previous_offsets.y = offset;
    ui->sliderMoveY->setSliderPosition(offset);
    ui->moveY->setValue(offset);
}

void MainWindow::SlotMoveObjectZ(int offset) {
    if (offset == previous_offsets.z) {
        return;
    }
    controller.MoveScene(0, 0, offset - previous_offsets.z);
    previous_offsets.z = offset;
    ui->sliderMoveZ->setSliderPosition(offset);
    ui->moveZ->setValue(offset);
}

void MainWindow::SlotRotateObjectX(int angle_deg) {
    if (angle_deg == previous_rotation.x) {
        return;
    }
    controller.RotateScene((angle_deg - previous_rotation.x) * M_PI / 180, 0, 0);
    previous_rotation.x = angle_deg;
    ui->sliderRotateX->setSliderPosition(angle_deg);
    ui->rotateX->setValue(angle_deg);
}

void MainWindow::SlotRotateObjectY(int angle_deg) {
    if (angle_deg == previous_rotation.y) {
        return;
    }
    controller.RotateScene(0, (angle_deg - previous_rotation.y) * M_PI / 180 , 0);
    previous_rotation.y = angle_deg;
    ui->sliderRotateY->setSliderPosition(angle_deg);
    ui->rotateY->setValue(angle_deg);
}

void MainWindow::SlotRotateObjectZ(int angle_deg) {
    if (angle_deg == previous_rotation.z) {
        return;
    }
    controller.RotateScene(0, 0, (angle_deg - previous_rotation.z) * M_PI / 180);
    previous_rotation.z = angle_deg;
    ui->sliderRotateZ->setSliderPosition(angle_deg);
    ui->rotateZ->setValue(angle_deg);
}

void MainWindow::SlotScaleObjectXYZ(int scale) {
    if (scale == previous_scales.x) {
        return;
    }
    controller.ScaleScene(scale / previous_scales.x, scale / previous_scales.y, scale / previous_scales.z);
    previous_scales.x = scale;
    previous_scales.y = scale;
    previous_scales.z = scale;
    ui->sliderScale->setSliderPosition(scale);
    ui->scale->setValue(scale);
}

void MainWindow::SlotChangeTypeProjection(int ind_type_proj) {
    scene_params.type_projection = static_cast<SceneParameters::TypeProjection>(ind_type_proj);
    Notify();
}

void MainWindow::SlotChangeBackground() {
    QColor color = QColorDialog::getColor(scene_params.background_color);
    if (color.isValid()) {
        ui->backgroundColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue()));
        scene_params.background_color = std::move(color);
        Notify();
    }
}

void MainWindow::SlotChangeEdgeType(int ind_edge_type) {
    scene_params.edge_type = static_cast<SceneParameters::TypeEdges>(ind_edge_type);
    Notify();
}

void MainWindow::SlotChangeVertexType(int ind_vertex_type) {
    scene_params.vertex_type = static_cast<SceneParameters::TypeVertex>(ind_vertex_type);
    Notify();
}

void MainWindow::SlotChangeEdgeWidth(int width) {
    scene_params.edge_width = width;
    Notify();
}

void MainWindow::SlotChangeVertexSize(int size) {
    scene_params.vertex_size = size;
    Notify();
}

void MainWindow::SlotChangeEdgeColor() {
    QColor color = QColorDialog::getColor(scene_params.edge_color);
    if (color.isValid()) {
        ui->lineColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue()));
        scene_params.edge_color = std::move(color);
        Notify();
    }
}

void MainWindow::SlotChangeVertexColor() {
    QColor color = QColorDialog::getColor(scene_params.vertex_color);
    if (color.isValid()) {
        ui->vertexColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue()));
        scene_params.vertex_color = std::move(color);
        Notify();
    }
}

void MainWindow::SlotSelectGifPath() {
    QString new_dir = QFileDialog::getExistingDirectory(0, "Выбор директории записи gif", "./");
    if (!new_dir.isEmpty()) {
        gif_dir = new_dir;
        ui->gifPath->setText(gif_dir);
        ui->gifPath->setToolTip(gif_dir);
    }

}

void MainWindow::SlotSelectScreenPath() {
    QString new_dir = QFileDialog::getExistingDirectory(0, "Выбор директории записи скринов", "./");
    if (!new_dir.isEmpty()) {
        screen_dir = new_dir;
        ui->screenPath->setText(screen_dir);
        ui->screenPath->setToolTip(screen_dir);
    }
}

void MainWindow::SlotMakeGif() {
    // 640x480, 10fps, 5s
    count_frames = 0;
    int delay = 100;
    int width = 640;
    int height = 480;
    QString uniq_name = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-z");
    QString f_name = QString("%1/video_%2.gif").arg(gif_dir).arg(uniq_name);
    GifBegin(&g, f_name.toStdString().c_str(), width, height, delay);
    CreateFrameToGif();
}

void MainWindow::CreateFrameToGif() {
    if (count_frames > 50) {
        GifEnd(&g);
        return;
    }
    int delay = 100;
    int width = 640;
    int height = 480;
    GifWriteFrame(&g, controller.GetFrameBuffer().scaled(width, height).bits(), width, height, 10);
    QTimer::singleShot(delay, this, SLOT(CreateFrameToGif()));
    ++count_frames;
}

void MainWindow::SlotPrintScreenBMP() {
    MakeScreenshot("bmp");
}

void MainWindow::SlotPrintScreenJPEG() {
    MakeScreenshot("jpeg");
}

void MainWindow::MakeScreenshot(QString extension) {
    QImage img = controller.GetFrameBuffer();
    QString uniq_name = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-z");
    img.save(QString("%1/image_%2.%3").arg(screen_dir).arg(uniq_name).arg(extension));
}

void MainWindow::wheelEvent(QWheelEvent *event) {
    if(event-> delta() > 0){
        ui->sliderScale->setSliderPosition(previous_scales.x * 1.1);
    } else {
        ui->sliderScale->setSliderPosition(previous_scales.x / 1.1);
    }
}



//void MainWindow::mousePressEvent(QMouseEvent *event) {
//    if (event->button() == Qt::LeftButton) {
//        mouse_event_x = event->pos().x();
//        mouse_event_y = event->pos().y();
//    }
//}

//void MainWindow::mouseMoveEvent(QMouseEvent *event) {
//    if(event->buttons() == Qt::LeftButton) {
//        int delta_deg_y = (event->pos().x() - mouse_event_x) * 0.01;
//        int delta_deg_x = (event->pos().y() - mouse_event_y) * 0.01;
//        int angle_deg_y = previous_rotation.y - delta_deg_y;
//        int angle_deg_x = previous_rotation.x - delta_deg_x;
//        controller.RotateScene(delta_deg_x * M_PI / 180, delta_deg_y * M_PI / 180, 0);
//        previous_rotation.x = angle_deg_x;
//        previous_rotation.y = angle_deg_y;
//        ui->sliderRotateY->setSliderPosition((angle_deg_y  > 180) ? -180 + angle_deg_y % 180 : ((angle_deg_y < -180) ? 180 - angle_deg_y % 180 : angle_deg_y));
//        ui->sliderRotateX->setSliderPosition((angle_deg_x  > 180) ? -180 + angle_deg_x % 180 : ((angle_deg_x < -180) ? 180 - angle_deg_x % 180 : angle_deg_x));
//        ui->rotateY->setValue((angle_deg_y  > 180) ? -180 + angle_deg_y % 180 : ((angle_deg_y < -180) ? 180 - angle_deg_y % 180 : angle_deg_y));
//        ui->rotateX->setValue((angle_deg_x  > 180) ? -180 + angle_deg_x % 180 : ((angle_deg_x < -180) ? 180 - angle_deg_x % 180 : angle_deg_x));
//    }
//}

} // namespace s21
