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

    this->members.at(curr_title).add_child(new_title);
}

auto OrgChart::get_members() {
    return &(this->members);
}

OrgChart::LevelOrder OrgChart::begin_level_order() {
    return OrgChart::LevelOrder{root};
}

OrgChart::LevelOrder OrgChart::end_level_order() {
    return OrgChart::LevelOrder();
}

OrgChart::LevelOrder OrgChart::begin() {
    return OrgChart::LevelOrder();
}

OrgChart::LevelOrder OrgChart::end() {
    return OrgChart::LevelOrder();
}

OrgChart::ReverseLevelOrder OrgChart::begin_reverse_order() {
    return OrgChart::ReverseLevelOrder();
}

OrgChart::ReverseLevelOrder OrgChart::end_reverse_order() {
    return OrgChart::ReverseLevelOrder();
}

OrgChart::PreOrder OrgChart::begin_preorder() {
    return OrgChart::PreOrder();
}

OrgChart::PreOrder OrgChart::end_preorder() {
    return OrgChart::PreOrder();
}

/** Node Class */
int OrgChart::Node::size() {

    return 0;
}

std::ostream &ariel::operator<<(std::ostream &ostream, OrgChart::Node &node) {
    return <#initializer#>;
}

void OrgChart::Node::add_child(const std::string& new_child_title) {

}

void OrgChart::Node::set_title(std::string _title) {
    this->title = std::move(_title);

}

std::ostream &ariel::operator<<(std::ostream &ostream, OrgChart &node) {
    return <#initializer#>;
}



/** Level Order Class */



OrgChart::Node &OrgChart::LevelOrder::operator=(OrgChart::Node &) {

    return <#initializer#>;
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
