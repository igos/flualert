<?php

/**
 * This is the main Web application configuration.
 * Any writable CWebApplication properties can be configured here.
 * @author Szymon P. Peplinski
 */
return array(
	'basePath'=>dirname(__FILE__).DIRECTORY_SEPARATOR.'../',
	
	// title
	'name'=>'FluAlert',
	
	// language
	'language'=>'en',
	
	// preloading 'log' component
	'preload'=>array(
		'log',
	),
	
	// autoloading model and component classes
	'import'=>array(
		'application.models.*',
		'application.components.*',
		'application.vendors.*',
	),
	
	// application components
	'components'=>array(
		'urlManager'=>array(
			'urlFormat'=>'path',
			'showScriptName'=>false,
			'rules'=>array(
				'<controller:\w+>/<id:\d+>'=>'<controller>/view',
				'<controller:\w+>/<action:\w+>/<id:\d+>'=>'<controller>/<action>',
				'<controller:\w+>/<action:\w+>'=>'<controller>/<action>',
			),
		),
		'coreMessages'=>array(
			'basePath'=>null,
		),
		'db'=>array(
			'connectionString'=>'sqlite:/Projects/Hackwaw/FluAlert/Backend/public/protected/data/db.sqlite',
			'emulatePrepare'=>true,
			'tablePrefix'=>'tbl_',
			'charset'=>'utf8',
		),
		'errorHandler'=>array(
			// use 'site/error' action to display errors
			'errorAction'=>'site/error',
		),
		'log'=>array(
			'class'=>'CLogRouter',
			'routes'=>array(
				array(
					'class'=>'CFileLogRoute',
					'logFile'=>'web.log',
					'levels'=>'error, warning',
				),
				array(
					'class'=>'CFileLogRoute',
					'logFile'=>'web_trace.log',
					'levels'=>'trace',
				),
			),
		),
	),
	
	// application-level parameters that can be accessed
	// using Yii::app()->params['paramName']
	'params'=>array(
		'authorEmail'=>'szymon.peplinski@facebook.com',
	),
);
