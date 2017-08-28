#include "CFContactListener.h"

void CFContactListener::BeginContact(b2Contact* contact){
    CFNode* nodeA = (CFNode*)contact->GetFixtureA()->GetBody()->GetUserData();
    CFNode* nodeB = (CFNode*)contact->GetFixtureB()->GetBody()->GetUserData();
    if(nodeA == NULL || nodeB == NULL){
        return;
    }
    nodeA->onConflict(contact, nodeB);
    nodeB->onConflict(contact, nodeA);
}

// Called when two fixtures cease to touch.
void CFContactListener::EndContact(b2Contact* contact){
}
