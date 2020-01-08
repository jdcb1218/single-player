<?php

function trivia_reply_page() {
  return theme('trivia_template');
}

function ajax_reply_callback(){
  Global $user;
  print('winning-player' . '/' . $user->uid);
}

function trivia_alter_question_true_false(&$form, &$form_state, $form_id){
    $key_question = array_keys($form['question']); 
    $nid_question = $key_question[FALSE];
    $node_tf = node_load($nid_question);
    
    if (isset($form['question'][$nid_question]['answer']['#options'])) {
      $data_feedback = theme('html_tag',
        array(
          'element' => array(
            '#tag' => 'div',
            '#attributes' => array(
              'id' => 'myModal',
              'class' => 'modal fade',
            ),
            '#value' => $node_tf->feedback['value'],
          ),
        )
      );

     $img_true = theme('image', array('path' => 'sites/all/themes/custom/trivia/img/img-true-trans.png', 
                          'attributes' => array('class' => 'ico-true', 'id' => 'true-ico')
                 ));

     $img_false = theme('image', array('path' => 'sites/all/themes/custom/trivia/img/img-false-trans.png', 
                          'attributes' => array('class' => 'ico-false', 'id' => 'false-ico')
                  ));

      foreach ($form['question'][$nid_question]['answer']['#options'] as $key => $value) {
         $img_question = ($key == 0) ?  $img_false: $img_true;
         if ($key == $node_tf->correct_answer) {
            $render = array('#type' => 'item',
                            '#prefix' => '<div class="correct">',
                            '#markup' => $img_question,
                            '#suffix' => '<div class="img-borde"></div></div>', 
            );
          }else{
             $render = array('#type' => 'item',
                              '#prefix' => '<div class="incorrect">',
                              '#markup' => $img_question,
                              '#suffix' => '<div class="img-borde"></div></div>', 
             ); 
          }
       $form['question'][$nid_question]['answer']['#options'][$key] = render($render); 
      }
      $form['question'][$nid_question]['answer']['#options']['feedback'] = render($data_feedback);
    }  
}

function trivia_reidrect(){
  if (current_path() == 'node/12/take/ajax_logout') {
      drupal_goto('user/logout');
  }  
  if (arg(1) == 'node' && is_numeric(arg(2)) && arg(3) == 'take' && arg(4) == 'ajax_logout') {
     drupal_goto('user/logout');
  }
  if (drupal_session_started() == FALSE && current_path() != 'user/register' && current_path() != 'user') {
     drupal_goto('<front>');
  }
}