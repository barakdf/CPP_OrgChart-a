//
// Created by barak on 16/05/2022.
//

#include "OrgChart.hpp"

#include <utility>

using namespace ariel;

OrgChart &OrgChart::add_root(const std::string& title) {
    if (this->root == nullptr) {
        Node e(title, 0);
        this->members.insert({title,e});
    } else {
        this->root->set_title(title);
    }
    return *this;
}

OrgChart &OrgChart::add_sub(const std::string& curr_title, const std::string& new_title) {
    if (this->members.find(curr_title) == this->members.end()) {
    }

    Node *parent = &(members.at(curr_title));
    Node child{new_title, parent->get_num_childs()};
    this->members.insert({new_title, child});
    this->members.at(curr_title).add_child(&this->members.at(new_title));
}

auto OrgChart::get_members() {
    return &(this->members);
}

OrgChart::LevelOrder OrgChart::begin_level_order() {
    return OrgChart::LevelOrder{this->root};
}

OrgChart::LevelOrder OrgChart::end_level_order() {
    return OrgChart::LevelOrder{nullptr};
}

OrgChart::LevelOrder OrgChart::begin() {
    return this->begin_level_order();
}

OrgChart::LevelOrder OrgChart::end() {
    return this->end_level_order();
}

OrgChart::ReverseLevelOrder OrgChart::begin_reverse_order() {
    return OrgChart::ReverseLevelOrder{};
}

OrgChart::ReverseLevelOrder OrgChart::end_reverse_order() {
    return OrgChart::ReverseLevelOrder{nullptr};
}

OrgChart::PreOrder OrgChart::begin_preorder() {
    return OrgChart::PreOrder{this->root};
}

OrgChart::PreOrder OrgChart::end_preorder() {
    return OrgChart::PreOrder{nullptr};
}

std::ostream &ariel::operator<<(std::ostream &ostream, OrgChart &orgChart) {
    ostream << "hi";
    return ostream;
}

/** ------------ Node Class */

size_t OrgChart::Node::get_num_childs() {

    return 0;
}

std::ostream &ariel::operator<<(std::ostream &ostream, OrgChart::Node &node) {
    ostream << node.title << '\n';

    return ostream;
}

void OrgChart::Node::add_child(Node *child) {

    this->childs.push_back(child);

}

void OrgChart::Node::set_title(std::string _title) {
    this->title = std::move(_title);

}





/** Level Order Class */



OrgChart::LevelOrder &OrgChart::LevelOrder::operator=(const OrgChart::LevelOrder & levelOrder) {
    this->pointer_to_current_node = levelOrder.pointer_to_current_node;


    return *this;
}

OrgChart::Node &OrgChart::LevelOrder::operator*() const {
    return <#initializer#>;
}

OrgChart::Node *OrgChart::LevelOrder::operator&() const {
    return nullptr;
}

OrgChart::Node *OrgChart::LevelOrder::operator->() const {
    return nullptr;
}

OrgChart::LevelOrder &OrgChart::LevelOrder::operator++() {
    return <#initializer#>;
}

const OrgChart::LevelOrder OrgChart::LevelOrder::operator++(int) {
    return OrgChart::LevelOrder();
}

bool OrgChart::LevelOrder::operator==(const OrgChart::LevelOrder &other) {
    return false;
}

bool OrgChart::LevelOrder::operator!=(const OrgChart::LevelOrder &other) {
    return false;
}
