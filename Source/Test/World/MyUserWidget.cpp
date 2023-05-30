// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "Components/EditableTextBox.h"
#include "Blueprint/WidgetNavigation.h"


void UMyUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextBox1->SetNavigationRuleExplicit(EUINavigation::Down, TextBox2);
	TextBox1->SetNavigationRuleExplicit(EUINavigation::Up, TextBox2);
	TextBox1->SetNavigationRuleExplicit(EUINavigation::Left, TextBox2);
	TextBox1->SetNavigationRuleExplicit(EUINavigation::Right, TextBox2);
	TextBox1->SetNavigationRuleExplicit(EUINavigation::Next, TextBox2);
	TextBox1->SetNavigationRuleExplicit(EUINavigation::Previous, TextBox2);
	TextBox2->SetNavigationRuleExplicit(EUINavigation::Down, TextBox1);
	TextBox2->SetNavigationRuleExplicit(EUINavigation::Up, TextBox1);
	TextBox2->SetNavigationRuleExplicit(EUINavigation::Left, TextBox1);
	TextBox2->SetNavigationRuleExplicit(EUINavigation::Right, TextBox1);
	TextBox2->SetNavigationRuleExplicit(EUINavigation::Next, TextBox1);
	TextBox2->SetNavigationRuleExplicit(EUINavigation::Previous, TextBox1);
}