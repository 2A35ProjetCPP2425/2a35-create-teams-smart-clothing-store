#include "statistiquesdialog.h"
#include "ui_statistiquesdialog.h"
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>  // Assurez-vous que cette ligne est incluse

StatistiquesDialog::StatistiquesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatistiquesDialog)
{
    ui->setupUi(this);
    genererGraphiqueFournisseursParBanque();  // Appel pour générer le graphique
}

StatistiquesDialog::~StatistiquesDialog()
{
    delete ui;
}

void StatistiquesDialog::genererGraphiqueFournisseursParBanque()
{
    // Supprimer tout contenu précédent dans le conteneur du graphique
    QLayout *existingLayout = ui->conteneurGraphique->layout();
    if (existingLayout) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0))) {
            delete item->widget();
            delete item;
        }
        delete existingLayout;
    }

    // Récupérer le nombre total de fournisseurs
    int totalFournisseurs = 0;
    QSqlQuery totalQuery;
    totalQuery.prepare("SELECT COUNT(*) FROM fournisseurs");
    if (totalQuery.exec() && totalQuery.next()) {
        totalFournisseurs = totalQuery.value(0).toInt();
    }

    // Créer un label pour afficher le nombre total de fournisseurs
    QLabel *labelTotalFournisseurs = new QLabel("Nombre total de fournisseurs : " + QString::number(totalFournisseurs));
    labelTotalFournisseurs->setAlignment(Qt::AlignCenter);  // Centrer le texte du label

    // Personnaliser le texte du label (mettre en gras, augmenter la taille et changer la couleur)
    QFont font = labelTotalFournisseurs->font();
    font.setBold(true);        // Mettre le texte en gras
    font.setPointSize(14);     // Agrandir la taille de la police
    labelTotalFournisseurs->setFont(font);

    // Modifier la couleur du texte du label en blanc
    labelTotalFournisseurs->setStyleSheet("color: white;");

    // Créer une nouvelle série pour le graphique (ex: graphique circulaire)
    QPieSeries *series = new QPieSeries();

    // Préparer la requête pour récupérer les fournisseurs par banque
    QSqlQuery query;
    query.prepare("SELECT INFO_BANC, COUNT(*) FROM fournisseurs GROUP BY INFO_BANC");

    if (!query.exec()) {
        // En cas d'échec de la requête, afficher l'erreur dans la console
        qDebug() << "Erreur de la requête : " << query.lastError();
        return;
    }

    // Ajouter les résultats de la requête au graphique
    while (query.next()) {
        // Récupérer le nom de la banque et le nombre de fournisseurs
        QString bankName = query.value(0).toString();
        int supplierCount = query.value(1).toInt();

        // Ajouter un slice (partie du graphique circulaire)
        QPieSlice *slice = series->append(bankName, supplierCount);
        slice->setLabelVisible(true);  // Afficher les labels (noms des banques)
    }

    // Créer le graphique et y ajouter la série
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des fournisseurs par banque");

    // Créer la vue pour afficher le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Activer l'anti-aliasing pour une meilleure qualité d'affichage

    // Créer un nouveau layout pour ajouter le label et le graphique
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(labelTotalFournisseurs);  // Ajouter le label du nombre total de fournisseurs
    layout->addWidget(chartView);  // Ajouter le graphique

    // Définir ce layout pour le conteneur graphique
    ui->conteneurGraphique->setLayout(layout);

    // Redimensionner la vue du graphique pour qu'elle prenne la taille du conteneur
    chartView->resize(ui->conteneurGraphique->size());
}


