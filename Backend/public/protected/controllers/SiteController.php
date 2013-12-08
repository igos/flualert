<?php

/**
 * SiteController is the default controller to handle user requests.
 * @author Szymon P. Peplinski
 */
class SiteController extends Controller
{
	public function actions(){
		return array(
			// page action renders "static" pages stored under 'protected/views/site/pages'
			// They can be accessed via: index.php?r=site/page&view=FileName
			'page'=>array(
				'class'=>'CViewAction',
			),
		);
	}
	
	/**
	 * This is the default 'index' action that is invoked
	 * when an action is not explicitly requested by users.
	 */
	public function actionIndex()
	{
		$id=intval(Yii::app()->request->getQuery('app_data',0));
		$url=Yii::app()->request->getQuery('url','');
		
		//Yii::app()->request->getQuery('id');
		$this->render('index',array(
			'id'=>$id,
			'url'=>$url,
		));
	}
	
	/**
	 * This is the action to handle external exceptions.
	 */
	public function actionError()
	{
		if($error=Yii::app()->errorHandler->error)
		{
			if(Yii::app()->request->isAjaxRequest)
				echo $error['message'];
			else
				$this->render('error', $error);
				//$this->redirect(Yii::app()->homeUrl); // Redirect home page.
	    }
	}
	
	/**
	 * Displays the desktop page
	 */
	public function actionLocale()
	{
		$this->layout=false;
		header('Content-type: application/json');
		$arr=include dirname(__FILE__).'/../messages/'.Yii::app()->language.'/app.php';
		echo CJavaScript::jsonEncode($arr);
		Yii::app()->end();
	}
	
	/**
	 * Test insert
	 */
	public function actionInsert()
	{
		$this->layout=false;
		
		$err=null;
		
		try
		{
			$connection=Yii::app()->db;
			$connection->createCommand(
				"INSERT INTO tbl_axis (id, time, x, y, z) VALUES ( :sensorId, :time, :x, :y, :z )"
			)->execute(
				array(
					':sensorId'=>1,
					':time'=>3,
					':x'=>2.23,
					':y'=>3.34,
					':z'=>4.34,
				)
			);
		}
		catch( Exception $e )
		{
			$err=serialize( $e );
		}
		
		$arr=array(
			'err'=>$err,
		);
		
		header('Content-type: application/json');
		echo CJavaScript::jsonEncode($arr);
		
		Yii::app()->end();
	}
}
