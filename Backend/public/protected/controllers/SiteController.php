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
		
		$pattern = "/^[ATH1234]{1,2}[,][0-9\-.]{1,10}/i";
		$data=Yii::app()->request->getQuery('data','');
		$array=explode(";", $data);
		
		try
		{
			$connection=Yii::app()->db;
			$transaction=$connection->beginTransaction();
			
			foreach($array as $value)
			{
			    if(preg_match($pattern,$value)) // use only valid records.
				{
					$values=explode(",",$value);
					$type = substr($values[0],0,1);
					$id = intval(substr($values[0],1,1));
					$x = $values[1];
					//echo $type.' '.$id.' '.$x."\n";
					
					$tbl=null;
					if($type=='A')
					{
						$tbl='tbl_axis';
					}
					elseif($type=='T')
					{
						$tbl='tbl_temperature';
					}
					elseif($type=='H')
					{
						$tbl='tbl_heartrate';
					}
					
					if(isset($tbl)&&!empty($tbl))
					{
						$connection->createCommand(
							"INSERT INTO $tbl (id, time, value) VALUES ( :sensorId, :time, :value )"
						)->execute(
							array(
								':sensorId'=>$id,
								':time'=>null,
								':value'=>$x,
							)
						);
					}
				}
			}
			
			$transaction->commit();
		}
		catch( Exception $e )
		{
			$transaction->rollback();
			$err=serialize( $e );
		}
		
		$arr=array(
			'err'=>$err,
		);
		
		header('Content-type: application/json');
		echo CJavaScript::jsonEncode($arr);
		
		Yii::app()->end();
	}
	
	/**
	 * Get sensor data
	 */
	public function actionSensor()
	{
		$this->layout=false;
		
		$type=Yii::app()->request->getQuery('type','');
		if($type=='A')
		{
			$tbl='tbl_axis';
		}
		elseif($type=='T')
		{
			$tbl='tbl_temperature';
		}
		elseif($type=='H')
		{
			$tbl='tbl_heartrate';
		}
		
		$err=null;
		
		try
		{
			$connection=Yii::app()->db;
			$row = $connection->createCommand( 
				"SELECT value FROM $tbl ORDER BY idx DESC LIMIT 1;"
			)->queryRow();
		}
		catch( Exception $e )
		{
			$err=serialize( $e );
		}
		;
		
		if( isset($err)&&!empty($err) )
		{
			$arr=array(
				'err'=>$err,
			);
		}
		else
		{
			$arr=array(
				'value'=>$row[ 'value' ],
			);
		}
		
		header('Content-type: application/json');
		echo CJavaScript::jsonEncode($arr);
		
		Yii::app()->end();
	}
	
	/**
	 * Clear table
	 */
	public function actionClear()
	{
		$this->layout=false;
		
		$err=null;
		
		$type=Yii::app()->request->getQuery('type','');
		if($type=='A')
		{
			$tbl='tbl_axis';
		}
		elseif($type=='T')
		{
			$tbl='tbl_temperature';
		}
		elseif($type=='H')
		{
			$tbl='tbl_heartrate';
		}
		
		if(isset($tbl)&&!empty($tbl))
		{
			try
			{
				$connection=Yii::app()->db;
				$transaction=$connection->beginTransaction();
				$connection->createCommand( "DELETE FROM $tbl" )->execute();
				$transaction->commit();
			}
			catch( Exception $e )
			{
				$transaction->rollback();
				$err=serialize( $e );
			}
		}
		
		$arr=array(
			'err'=>$err,
		);
		
		header('Content-type: application/json');
		echo CJavaScript::jsonEncode($arr);
		
		Yii::app()->end();
	}
}
