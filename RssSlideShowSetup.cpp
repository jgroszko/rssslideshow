#include <kaboutapplicationdialog.h>

#include "RssSlideShowSetup.h"

RssSlideShowSetup::RssSlideShowSetup(QWidget *aParent)
	: KDialog(aParent)
{
	setCaption(i18n( "Setup RSS Slide Show Screen Saver" ));
	setButtons(Ok|Cancel|Help);
	setDefaultButton(Ok);
	setModal(true);
	setButtonText( Help, i18n( "A&bout" ) );

	QWidget *main = new QWidget(this);
	setMainWidget(main);
	cfg = new RssSlideShowConfig(main);

	cfg->mPreview->setFixedSize(220, 170);
	cfg->mPreview->show();    // otherwise saver does not get correct size
	mSaver = new RssSlideShowSaver(cfg->mPreview->winId());

	connect(cfg->pushButton_AddFeed, SIGNAL(clicked()),this,SLOT(slotAddFeed()));
	connect(cfg->pushButton_RemoveFeed, SIGNAL(clicked()),this,SLOT(slotRemoveFeed()));

	connect(this,SIGNAL(okClicked()),this,SLOT(slotOk()));
	readSettings();
}

RssSlideShowSetup::~RssSlideShowSetup()
{
	delete mSaver;
}

//-----------------------------------------------------------------------------
void RssSlideShowSetup::readSettings()
{
	KConfigGroup config( KGlobal::config(), "Settings");

	cfg->mCbxRandom->setChecked(config.readEntry("ShowRandom", true));
	cfg->mCbxZoom->setChecked(config.readEntry("ZoomImages", false));
	cfg->mCbxShowName->setChecked(config.readEntry("PrintName", true));
	cfg->mCbxShowPath->setChecked(config.readEntry("PrintPath", false));
	cfg->mDelay->setValue(config.readEntry("Delay", 20));
	cfg->mDelay->setSuffix(ki18np(" second", " seconds"));
	cfg->mCbxRandomPosition->setChecked(config.readEntry("RandomPosition", false));
	//cfg->mCbxEffectsEnabled->setChecked(config.readEntry("EffectsEnabled", true));

	QStringList feeds = config.readEntry("Feeds").split("|");

	for(int i = 0; i < feeds.count(); i++)
		cfg->listWidget_Feeds->addItem(feeds.at(i));
}


//-----------------------------------------------------------------------------
void RssSlideShowSetup::writeSettings()
{
	KConfigGroup config( KGlobal::config(), "Settings");

	config.writeEntry("ShowRandom", cfg->mCbxRandom->isChecked());
	config.writeEntry("ZoomImages", cfg->mCbxZoom->isChecked());
	config.writeEntry("PrintName",  cfg->mCbxShowName->isChecked());
	config.writeEntry("PrintPath",  cfg->mCbxShowPath->isChecked());
	config.writeEntry("Delay", cfg->mDelay->value());
	config.writeEntry("RandomPosition", cfg->mCbxRandomPosition->isChecked());
	//config.writeEntry("EffectsEnabled", cfg->mCbxEffectsEnabled->isChecked());

	QStringList feeds;

	for(int i = 0; i < cfg->listWidget_Feeds->count(); i++)
	{
		QString feed = cfg->listWidget_Feeds->item(i)->text();
		if(!feed.isEmpty())
			feeds << feed;
	}

	config.writeEntry("Feeds", feeds.join("|"));

	config.sync();

	if (mSaver)
	{
		//mSaver->readConfig();
		mSaver->update();
	}
}


//-----------------------------------------------------------------------------

void RssSlideShowSetup::slotAddFeed()
{
	KUrl newFeed = KUrl::fromPathOrUrl(cfg->lineEdit_FeedToAdd->text());

	if(newFeed.isValid())
	{
		cfg->listWidget_Feeds->addItem(newFeed.url());
	}

	cfg->lineEdit_FeedToAdd->clear();

	writeSettings();
}

void RssSlideShowSetup::slotRemoveFeed()
{
	cfg->listWidget_Feeds->takeItem(cfg->listWidget_Feeds->currentRow());

	writeSettings();
}

//-----------------------------------------------------------------------------
void RssSlideShowSetup::slotOk()
{
	writeSettings();
	accept();
}
