TEMPLATE	= app
TARGET		= deplcl
CONFIG		+= release warn_on qt
DEFINES		= WITHCPP WITHJAVA WITHPHP WITHPYTHON WITHIDL
HEADERS		= ./UmlBaseExpansionRegion.h \
		  ./UmlBaseUseCaseDiagramDefinition.h \
		  ./UmlBaseView.h \
		  ./UmlUseCaseAssociation.h \
		  ./aDirection.h \
		  ./UmlChoicePseudoState.h \
		  ./UmlBaseStateAction.h \
		  ./UmlClassItem.h \
		  ./UmlStateAction.h \
		  ./UmlUseCaseView.h \
		  ./UmlBaseAttribute.h \
		  ./UmlOperation.h \
		  ./UmlBaseAccessVariableValueAction.h \
		  ./UmlBaseActivityAction.h \
		  ./UmlSubject.h \
		  ./anExpansionKind.h \
		  ./UmlDeploymentDiagram.h \
		  ./aVisibility.h \
		  ./UmlState.h \
		  ./UmlBaseNode.h \
		  ./UmlBaseArtifact.h \
		  ./UmlNode.h \
		  ./UmlFormalParameter.h \
		  ./UmlPseudoState.h \
		  ./UmlBaseActivityObject.h \
		  ./UmlBaseClassInstance.h \
		  ./UmlBaseOnSignalAction.h \
		  ./UmlBaseSubject.h \
		  ./UmlMessage.h \
		  ./UmlBaseEntryPointPseudoState.h \
		  ./UmlComponentDiagram.h \
		  ./UmlAttribute.h \
		  ./UmlBaseForkPseudoState.h \
		  ./UmlBaseClassItem.h \
		  ./TransitionBehavior.h \
		  ./UmlNcRelation.h \
		  ./UmlBaseDeploymentView.h \
		  ./OnInstanceCmd.h \
		  ./JavaSettingsCmd.h \
		  ./UmlActivityItem.h \
		  ./UmlBaseActivityPin.h \
		  ./UmlExpansionNode.h \
		  ./UmlParameterSet.h \
		  ./aMessageKind.h \
		  ./IdlSettings.h \
		  ./UmlBaseDeployment.h \
		  ./UmlSettings.h \
		  ./UmlBaseShallowHistoryPseudoState.h \
		  ./UmlCom.h \
		  ./PhpSettings.h \
		  ./UmlBaseParameterSet.h \
		  ./UmlObjectDiagram.h \
		  ./UmlClassDiagram.h \
		  ./StateBehavior.h \
		  ./UmlBaseUseCaseView.h \
		  ./UmlArtifact.h \
		  ./UmlStateDiagram.h \
		  ./UmlForkPseudoState.h \
		  ./UmlStereotype.h \
		  ./UmlShallowHistoryPseudoState.h \
		  ./CmdFamily.h \
		  ./UmlBaseJoinPseudoState.h \
		  ./UmlBaseSequenceDiagram.h \
		  ./UmlActivity.h \
		  ./UmlBaseClassInstanceReference.h \
		  ./UmlBaseCollaborationMessage.h \
		  ./UmlBaseFlow.h \
		  ./UmlBaseFragment.h \
		  ./UmlBaseSequenceDiagramDefinition.h \
		  ./UmlParameter.h \
		  ./CppSettings.h \
		  ./UmlBaseClass.h \
		  ./UmlFinalState.h \
		  ./UmlBaseUseCaseDiagram.h \
		  ./UmlBaseChoicePseudoState.h \
		  ./UmlBaseActivity.h \
		  ./UmlBaseActivityParameter.h \
		  ./UmlClassInstanceReference.h \
		  ./UmlUseCaseReference.h \
		  ./UmlBaseItem.h \
		  ./UmlComponentView.h \
		  ./UmlBasePackage.h \
		  ./ClassGlobalCmd.h \
		  ./MiscGlobalCmd.h \
		  ./UmlComponent.h \
		  ./SlotAttribute.h \
		  ./UmlActivityNode.h \
		  ./UmlBaseActivityDiagram.h \
		  ./UmlBaseSequenceMessage.h \
		  ./UmlBaseNcRelation.h \
		  ./UmlBaseRegion.h \
		  ./UmlBaseState.h \
		  ./UmlInitialPseudoState.h \
		  ./UmlActivityDiagram.h \
		  ./UmlBaseActivityNode.h \
		  ./UmlBaseExpansionNode.h \
		  ./UmlBaseParameter.h \
		  ./UmlClassInstance.h \
		  ./UmlBaseCollaborationDiagram.h \
		  ./PythonSettings.h \
		  ./UmlBaseClassDiagram.h \
		  ./PhpSettingsCmd.h \
		  ./UmlItem.h \
		  ./UmlJoinPseudoState.h \
		  ./UmlAccessVariableValueAction.h \
		  ./UmlActivityControlNodeClasses.h \
		  ./UmlCollaborationMessage.h \
		  ./UmlOnSignalAction.h \
		  ./UmlPinParameter.h \
		  ./UmlBaseStateDiagram.h \
		  ./UmlTerminatePseudoState.h \
		  ./UmlJunctionPseudoState.h \
		  ./UmlBaseComponentView.h \
		  ./SlotRelation.h \
		  ./UmlBaseActivityRegion.h \
		  ./UmlFragmentCompartment.h \
		  ./UmlUseCaseDiagramDefinition.h \
		  ./aParameterEffectKind.h \
		  ./PythonSettingsCmd.h \
		  ./UmlBaseUseCase.h \
		  ./PackageGlobalCmd.h \
		  ./UmlBaseOperation.h \
		  ./UmlBaseFormalParameter.h \
		  ./UmlBaseFinalState.h \
		  ./UmlActivityPin.h \
		  ./UmlBaseActivityActionClasses.h \
		  ./UmlBaseMessage.h \
		  ./UmlBaseTypeSpec.h \
		  ./UmlBaseUseCaseReference.h \
		  ./UmlExpansionRegion.h \
		  ./UmlFlow.h \
		  ./UmlSettingsCmd.h \
		  ./UmlBaseTerminatePseudoState.h \
		  ./UmlBaseRelation.h \
		  ./UmlDiagram.h \
		  ./UmlActivityActionClasses.h \
		  ./UmlBaseActivityControlNodeClasses.h \
		  ./UmlView.h \
		  ./UmlBaseExtraClassMember.h \
		  ./aRelationKind.h \
		  ./UmlClassMember.h \
		  ./JavaSettings.h \
		  ./UmlBaseComponent.h \
		  ./UmlExtraClassMember.h \
		  ./UmlClassView.h \
		  ./UmlClass.h \
		  ./UmlBaseActualParameter.h \
		  ./UmlActivityParameter.h \
		  ./UmlActivityRegion.h \
		  ./UmlBaseFragmentCompartment.h \
		  ./UmlCollaborationDiagramDefinition.h \
		  ./UmlSequenceMessage.h \
		  ./UmlTransition.h \
		  ./UmlBaseDeepHistoryPseudoState.h \
		  ./UmlBaseDeploymentDiagram.h \
		  ./UmlDeploymentView.h \
		  ./UmlBaseTransition.h \
		  ./UmlActivityAction.h \
		  ./UmlActivityControlNode.h \
		  ./UmlBasePinParameter.h \
		  ./UmlBaseUseCaseAssociation.h \
		  ./UmlFragment.h \
		  ./UmlSequenceDiagramDefinition.h \
		  ./UmlCollaborationDiagram.h \
		  ./UmlRegion.h \
		  ./UmlBaseComponentDiagram.h \
		  ./UmlBaseJunctionPseudoState.h \
		  ./UmlUseCaseDiagram.h \
		  ./UmlTypeSpec.h \
		  ./UmlBaseInitialPseudoState.h \
		  ./UmlSequenceDiagram.h \
		  ./FlowBehavior.h \
		  ./UmlBaseActivityControlNode.h \
		  ./UmlBuiltin.h \
		  ./UmlInterruptibleActivityRegion.h \
		  ./UmlActualParameter.h \
		  ./UmlStateItem.h \
		  ./UmlRelation.h \
		  ./UmlBaseClassView.h \
		  ./UmlPackage.h \
		  ./UmlExitPointPseudoState.h \
		  ./UmlEntryPointPseudoState.h \
		  ./anItemKind.h \
		  ./CppSettingsCmd.h \
		  ./UmlActivityObject.h \
		  ./UmlBaseCollaborationDiagramDefinition.h \
		  ./UmlBaseInterruptibleActivityRegion.h \
		  ./UmlBaseObjectDiagram.h \
		  ./aLanguage.h \
		  ./anOrdering.h \
		  ./IdlSettingsCmd.h \
		  ./UmlUseCase.h \
		  ./UmlBaseClassMember.h \
		  ./UmlBaseExitPointPseudoState.h \
		  ./UmlBaseDiagram.h \
		  ./UmlDeepHistoryPseudoState.h
SOURCES		= ./UmlBaseExpansionRegion.cpp \
		  ./UmlBaseUseCaseDiagramDefinition.cpp \
		  ./UmlBaseView.cpp \
		  ./UmlUseCaseAssociation.cpp \
		  ./aDirection.cpp \
		  ./UmlChoicePseudoState.cpp \
		  ./UmlBaseStateAction.cpp \
		  ./UmlClassItem.cpp \
		  ./UmlStateAction.cpp \
		  ./UmlUseCaseView.cpp \
		  ./UmlBaseAttribute.cpp \
		  ./UmlOperation.cpp \
		  ./UmlBaseAccessVariableValueAction.cpp \
		  ./UmlBaseActivityAction.cpp \
		  ./UmlSubject.cpp \
		  ./anExpansionKind.cpp \
		  ./UmlDeploymentDiagram.cpp \
		  ./aVisibility.cpp \
		  ./UmlState.cpp \
		  ./UmlBaseNode.cpp \
		  ./UmlBaseArtifact.cpp \
		  ./UmlNode.cpp \
		  ./UmlFormalParameter.cpp \
		  ./UmlPseudoState.cpp \
		  ./UmlBaseActivityObject.cpp \
		  ./UmlBaseClassInstance.cpp \
		  ./UmlBaseOnSignalAction.cpp \
		  ./UmlBaseSubject.cpp \
		  ./UmlMessage.cpp \
		  ./UmlBaseEntryPointPseudoState.cpp \
		  ./UmlComponentDiagram.cpp \
		  ./UmlAttribute.cpp \
		  ./UmlBaseForkPseudoState.cpp \
		  ./UmlBaseClassItem.cpp \
		  ./TransitionBehavior.cpp \
		  ./UmlNcRelation.cpp \
		  ./UmlBaseDeploymentView.cpp \
		  ./OnInstanceCmd.cpp \
		  ./JavaSettingsCmd.cpp \
		  ./UmlActivityItem.cpp \
		  ./UmlBaseActivityPin.cpp \
		  ./UmlExpansionNode.cpp \
		  ./UmlParameterSet.cpp \
		  ./aMessageKind.cpp \
		  ./IdlSettings.cpp \
		  ./UmlBaseDeployment.cpp \
		  ./UmlSettings.cpp \
		  ./UmlBaseShallowHistoryPseudoState.cpp \
		  ./UmlCom.cpp \
		  ./PhpSettings.cpp \
		  ./UmlBaseParameterSet.cpp \
		  ./UmlObjectDiagram.cpp \
		  ./UmlClassDiagram.cpp \
		  ./StateBehavior.cpp \
		  ./UmlBaseUseCaseView.cpp \
		  ./UmlArtifact.cpp \
		  ./UmlStateDiagram.cpp \
		  ./UmlForkPseudoState.cpp \
		  ./UmlStereotype.cpp \
		  ./UmlShallowHistoryPseudoState.cpp \
		  ./CmdFamily.cpp \
		  ./UmlBaseJoinPseudoState.cpp \
		  ./UmlBaseSequenceDiagram.cpp \
		  ./UmlActivity.cpp \
		  ./UmlBaseClassInstanceReference.cpp \
		  ./UmlBaseCollaborationMessage.cpp \
		  ./UmlBaseFlow.cpp \
		  ./UmlBaseFragment.cpp \
		  ./UmlBaseSequenceDiagramDefinition.cpp \
		  ./UmlParameter.cpp \
		  ./CppSettings.cpp \
		  ./UmlBaseClass.cpp \
		  ./UmlFinalState.cpp \
		  ./UmlBaseUseCaseDiagram.cpp \
		  ./UmlBaseChoicePseudoState.cpp \
		  ./UmlBaseActivity.cpp \
		  ./UmlBaseActivityParameter.cpp \
		  ./UmlClassInstanceReference.cpp \
		  ./UmlUseCaseReference.cpp \
		  ./UmlBaseItem.cpp \
		  ./UmlComponentView.cpp \
		  ./UmlBasePackage.cpp \
		  ./ClassGlobalCmd.cpp \
		  ./MiscGlobalCmd.cpp \
		  ./UmlComponent.cpp \
		  ./SlotAttribute.cpp \
		  ./UmlActivityNode.cpp \
		  ./UmlBaseActivityDiagram.cpp \
		  ./UmlBaseSequenceMessage.cpp \
		  ./UmlBaseNcRelation.cpp \
		  ./UmlBaseRegion.cpp \
		  ./UmlBaseState.cpp \
		  ./UmlInitialPseudoState.cpp \
		  ./UmlActivityDiagram.cpp \
		  ./UmlBaseActivityNode.cpp \
		  ./UmlBaseExpansionNode.cpp \
		  ./UmlBaseParameter.cpp \
		  ./UmlClassInstance.cpp \
		  ./UmlBaseCollaborationDiagram.cpp \
		  ./PythonSettings.cpp \
		  ./UmlBaseClassDiagram.cpp \
		  ./PhpSettingsCmd.cpp \
		  ./UmlItem.cpp \
		  ./UmlJoinPseudoState.cpp \
		  ./UmlAccessVariableValueAction.cpp \
		  ./UmlActivityControlNodeClasses.cpp \
		  ./UmlCollaborationMessage.cpp \
		  ./UmlOnSignalAction.cpp \
		  ./UmlPinParameter.cpp \
		  ./UmlBaseStateDiagram.cpp \
		  ./UmlTerminatePseudoState.cpp \
		  ./UmlJunctionPseudoState.cpp \
		  ./UmlBaseComponentView.cpp \
		  ./SlotRelation.cpp \
		  ./UmlBaseActivityRegion.cpp \
		  ./UmlFragmentCompartment.cpp \
		  ./UmlUseCaseDiagramDefinition.cpp \
		  ./aParameterEffectKind.cpp \
		  ./PythonSettingsCmd.cpp \
		  ./UmlBaseUseCase.cpp \
		  ./PackageGlobalCmd.cpp \
		  ./UmlBaseOperation.cpp \
		  ./UmlBaseFormalParameter.cpp \
		  ./UmlBaseFinalState.cpp \
		  ./UmlActivityPin.cpp \
		  ./UmlBaseActivityActionClasses.cpp \
		  ./UmlBaseMessage.cpp \
		  ./UmlBaseTypeSpec.cpp \
		  ./UmlBaseUseCaseReference.cpp \
		  ./UmlExpansionRegion.cpp \
		  ./UmlFlow.cpp \
		  ./UmlSettingsCmd.cpp \
		  ./Main.cpp \
		  ./UmlBaseTerminatePseudoState.cpp \
		  ./UmlBaseRelation.cpp \
		  ./UmlDiagram.cpp \
		  ./UmlActivityActionClasses.cpp \
		  ./UmlBaseActivityControlNodeClasses.cpp \
		  ./UmlView.cpp \
		  ./UmlBaseExtraClassMember.cpp \
		  ./aRelationKind.cpp \
		  ./UmlClassMember.cpp \
		  ./JavaSettings.cpp \
		  ./UmlBaseComponent.cpp \
		  ./UmlExtraClassMember.cpp \
		  ./UmlClassView.cpp \
		  ./UmlClass.cpp \
		  ./UmlBaseActualParameter.cpp \
		  ./UmlActivityParameter.cpp \
		  ./UmlActivityRegion.cpp \
		  ./UmlBaseFragmentCompartment.cpp \
		  ./UmlCollaborationDiagramDefinition.cpp \
		  ./UmlSequenceMessage.cpp \
		  ./UmlTransition.cpp \
		  ./UmlBaseDeepHistoryPseudoState.cpp \
		  ./UmlBaseDeploymentDiagram.cpp \
		  ./UmlDeploymentView.cpp \
		  ./UmlBaseTransition.cpp \
		  ./UmlActivityAction.cpp \
		  ./UmlActivityControlNode.cpp \
		  ./UmlBasePinParameter.cpp \
		  ./UmlBaseUseCaseAssociation.cpp \
		  ./UmlFragment.cpp \
		  ./UmlSequenceDiagramDefinition.cpp \
		  ./UmlCollaborationDiagram.cpp \
		  ./UmlRegion.cpp \
		  ./UmlBaseComponentDiagram.cpp \
		  ./UmlBaseJunctionPseudoState.cpp \
		  ./UmlUseCaseDiagram.cpp \
		  ./UmlTypeSpec.cpp \
		  ./UmlBaseInitialPseudoState.cpp \
		  ./UmlSequenceDiagram.cpp \
		  ./FlowBehavior.cpp \
		  ./UmlBaseActivityControlNode.cpp \
		  ./UmlBuiltin.cpp \
		  ./UmlInterruptibleActivityRegion.cpp \
		  ./UmlActualParameter.cpp \
		  ./UmlStateItem.cpp \
		  ./UmlRelation.cpp \
		  ./UmlBaseClassView.cpp \
		  ./UmlPackage.cpp \
		  ./UmlExitPointPseudoState.cpp \
		  ./UmlEntryPointPseudoState.cpp \
		  ./anItemKind.cpp \
		  ./CppSettingsCmd.cpp \
		  ./UmlActivityObject.cpp \
		  ./UmlBaseCollaborationDiagramDefinition.cpp \
		  ./UmlBaseInterruptibleActivityRegion.cpp \
		  ./UmlBaseObjectDiagram.cpp \
		  ./aLanguage.cpp \
		  ./anOrdering.cpp \
		  ./IdlSettingsCmd.cpp \
		  ./UmlUseCase.cpp \
		  ./UmlBaseClassMember.cpp \
		  ./UmlBaseExitPointPseudoState.cpp \
		  ./UmlBaseDiagram.cpp \
		  ./UmlDeepHistoryPseudoState.cpp

